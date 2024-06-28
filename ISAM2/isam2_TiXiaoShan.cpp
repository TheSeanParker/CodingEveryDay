
/**
 * A simple 2D pose slam example
 *  - The robot moves in a 2 meter square
 *  - The robot moves 2 meters each step, turning 90 degrees after each step
 *  - The robot initially faces along the X axis (horizontal, to the right in 2D)
 *  - We have full odometry between pose
 *  - We have a loop closure constraint when the robot returns to the first position
 *                             x5 -- x4
 *                              |        |
 *                   x1 -- x2 -- x3
 */

// Each variable in the system (poses and landmarks) must be identified with a unique key.
// We can either use simple integer keys (1, 2, 3, ...) or symbols (X1, X2, L1).
// Here we will use Symbols
#include <gtsam/inference/Symbol.h>

// We want to use iSAM2 to solve the pose optimazation problem incrementally, so
// include iSAM2 here
#include <gtsam/nonlinear/ISAM2.h>

// iSAM2 requires as input a set set of new factors to be added stored in a factor graph,
// and initial guesses for any new variables used in the added factors
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>

#include <vector>

// In planar SLAM example we use Pose2 variables (x, y, theta) to represent the robot poses
#include <gtsam/geometry/Pose2.h>

// We will use simple integer Keys to refer to the robot poses.
#include <gtsam/inference/Key.h>

// In GTSAM, measurement functions are represented as 'factors'. Several common factors
// have been provided with the library for solving robotics/SLAM/Bundle Adjustment problems.
// Here we will use Between factors for the relative motion described by odometry measurements.
// We will also use a Between Factor to encode the loop closure constraint
// Also, we will initialize the robot at the origin using a Prior factor.
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/slam/BetweenFactor.h>

// The nonlinear solvers within GTSAM are iterative solvers, meaning they linearize the
// nonlinear functions around an initial linearization point, then solve the linear system
// to update the linearization point. This happens repeatedly until the solver converges
// to a consistent set of variable values. This requires us to specify an initial guess
// for each variable, held in a Values container.
#include <gtsam/nonlinear/Values.h>
// https://heyijia.blog.csdn.net/article/details/53367268?spm=1001.2014.3001.5502
#include <gtsam/navigation/ImuBias.h>

using namespace std;
using namespace gtsam;

int main()
{
  // 向量保存好模拟的位姿和测量，到时候一个个往isam2里填加
  std::vector< BetweenFactor<Pose2> > gra;
  std::vector< Pose2 > initPose;

  //  For simplicity, we will use the same noise model for odometry and loop closures
  noiseModel::Diagonal::shared_ptr model = noiseModel::Diagonal::Sigmas(Vector3(0.2, 0.2, 0.1));

   // 下面是相对位置关系,从1个点到另外1个点
  gra.push_back(BetweenFactor<Pose2>(Symbol('x', 1), Symbol('x', 2), Pose2(2, 0, 0),              model));
  gra.push_back(BetweenFactor<Pose2>(Symbol('x', 2), Symbol('x', 3), Pose2(2, 0, M_PI_2), model));
  gra.push_back(BetweenFactor<Pose2>(Symbol('x', 3), Symbol('x', 4), Pose2(2, 0, M_PI_2), model));
  gra.push_back(BetweenFactor<Pose2>(Symbol('x', 4), Symbol('x', 5), Pose2(2, 0, M_PI_2), model));
  gra.push_back(BetweenFactor<Pose2>(Symbol('x', 5), Symbol('x', 2), Pose2(2, 0, M_PI_2), model));

  // 下面是初始位置关系,是当前位姿的点([不准确]的当前点)
  initPose.push_back( Pose2(0.5, 0.0,  0.2           ));
  initPose.push_back( Pose2(2.3, 0.1, -0.2          ));
  initPose.push_back( Pose2(4.1, 0.1,  M_PI_2 ));
  initPose.push_back( Pose2(4.0, 2.0,  M_PI      ));
  initPose.push_back( Pose2(2.1, 2.1, -M_PI_2));

  // Create an iSAM2 object. Unlike iSAM1, which performs periodic batch steps to maintain proper linearization
  // and efficient variable ordering, iSAM2 performs partial relinearization/reordering at each step. A parameter
  // structure is available that allows the user to set various properties, such as the relinearization threshold
  // and type of linear solver. For this example, we we set the relinearization threshold small so the iSAM2 result
  // will approach the batch result.

  ISAM2Params parameters;
  parameters.relinearizeThreshold = 0.01;
  parameters.relinearizeSkip = 1;
  ISAM2 isam2(parameters);

  // Create a Factor Graph and Values to hold the new data
  // 注意isam2的graph里只添加isam2更新状态以后新测量到的约束
  NonlinearFactorGraph graph;
  Values initialEstimate;

  gtsam::imuBias::ConstantBias prevBias_;
  prevBias_ = gtsam::imuBias::ConstantBias();
  std::cout<<"--------------------prevBias_="<<prevBias_<<std::endl;
  // the first pose don't need to update
  for( int i =0; i<5 ;i++)
  {
          // Add an initial guess for the current pose
           initialEstimate.insert(Symbol('x', i+1), initPose[i]);
           if(i == 0)
           {
               //  Add a prior on the first pose, setting it to the origin
               // A prior factor consists of a mean and a noise model (covariance matrix)
               noiseModel::Diagonal::shared_ptr priorNoise = noiseModel::Diagonal::Sigmas(Vector3(0.3, 0.3, 0.1));
               graph.push_back(PriorFactor<Pose2>(Symbol('x', 1), Pose2(0, 0, 0), priorNoise));
               cout<<"1------------------------graph.size() ="<<graph.size()<<std::endl;
           }else
           {
               cout<<"a------------------------graph.size() ="<<graph.size()<<std::endl;
               graph.push_back(gra[i-1]);  
               // vector[0] represents the first number
               // ie: when i = 1 , robot at pos2,  there is a edge gra[0] between pos1 and pos2
               
               cout<<"b------------------------graph.size() ="<<graph.size()<<std::endl;
               if(i == 4)
               {
                   graph.push_back(gra[4]);  //  when robot at pos5, there two edge, one is pos4 ->pos5, another is pos5->pos2  (grad[4])
               }
               cout<<"2------------------------graph.size() ="<<graph.size()<<std::endl;
               isam2.update(graph, initialEstimate);
               isam2.update();

               graph.resize(0);
               initialEstimate.clear();
               
               Values currentEstimate = isam2.calculateEstimate();//这个估计出来数据,但不会显式打印出来
               cout << "****************************************************" << endl;
               cout <<"iter num="<<std::endl;
               cout << "Frame " << i << ": " << endl; //前后2种结构,主要在这一步不同,贺一家博士贺TiXiaoShan不同的地方
               graph.print("---------FactorGraph:");
                //    print out graph 
                //    ISAM2::update_count_;
               currentEstimate.print("Current estimate: ");

               // Clear the factor graph and values for the next iteration
               // 特别重要，update以后，清空原来的约束。已经加入到isam2的那些会用bayes tree保管，你不用操心了。
           }
  }
  return 0; 
}
