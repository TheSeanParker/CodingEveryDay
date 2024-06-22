/**
 * @file ImuFactorExample2
 * @brief Test example for using GTSAM ImuFactor and ImuCombinedFactor with ISAM2. Simplify and add graphviz by Zeal
 * @author Robert Truax
 * @author Zeal
 * @author compatible with gtsam 4.0.2
 */
#include <gtsam/geometry/PinholeCamera.h>
#include <gtsam/geometry/Cal3_S2.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/navigation/Scenario.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/slam/BetweenFactor.h>
#include <vector>
#include <gtsam/slam/PriorFactor.h>
#include <Eigen/Dense>
#include <fstream>
using namespace std;
using namespace gtsam;

// Shorthand for velocity and pose variables
using symbol_shorthand::V;
using symbol_shorthand::X;
using symbol_shorthand::B;

const double kGravity = 9.81;

/* ************************************************************************* */
int main(int argc, char* argv[]) {
  // IMU 预积分器
  // 设置预积分器的噪声参数，这些噪声参数一般来自IMU的离线标定结果
  auto params = PreintegrationParams::MakeSharedU(kGravity);
  params->setAccelerometerCovariance(I_3x3 * 0.1);
  params->setGyroscopeCovariance(I_3x3 * 0.1);
  params->setIntegrationCovariance(I_3x3 * 0.1);
  params->setUse2ndOrderCoriolis(false);
  params->setOmegaCoriolis(Vector3(0, 0, 0));

  // 起点
  Pose3 pose_0(Rot3::Rodrigues(0, 0, 0), Point3(0,0,0));// 旋转+平移

  // 设置一个姿态仿真器，姿态沿着y轴以5m/s的速度前进，没有角度变化
  Vector3 angular_velocity_vector(0, 0, 0);
  Vector3 linear_velocity_vector(0, 5, 0);
  auto scenario = ConstantTwistScenario(angular_velocity_vector,linear_velocity_vector, pose_0);
  double delta_t = 1.0;// 设置仿真步长为1s

  NonlinearFactorGraph newgraph; // 设置一个非线性因子图
  ISAM2 isam;   // Create (incremental) ISAM2 solver
  Values initialEstimate, result;// 声明因子图的初始值和优化结果

  // 设置位姿的先验因子
  // 对应到上图中连接到变量x0的一元因子
  // 噪声设置为roll、pitch、yaw有0.1rad的标准差，x，y，z有30cm的标准差
  auto noise = noiseModel::Diagonal::Sigmas((Vector(6) << Vector3::Constant(0.1), Vector3::Constant(0.3)).finished());
  // 将位姿的先验因子加入因子图中
  newgraph.push_back(PriorFactor<Pose3>(X(0), pose_0, noise));
  // 将位姿0的初始值加入初始估计集合
  initialEstimate.insert(X(0), pose_0);

  // 设置IMU偏差的先验因子
  // 对应到上图中连接到变量b0的一元因子
  Key biasKey = Symbol('b', 0);
  auto biasnoise = noiseModel::Diagonal::Sigmas(Vector6::Constant(0.1));
  PriorFactor<imuBias::ConstantBias> biasprior(biasKey, imuBias::ConstantBias(),biasnoise);
  newgraph.push_back(biasprior); // 将IMU偏差b0的初始值加入初始估计集合
  initialEstimate.insert(biasKey, imuBias::ConstantBias());
  
  // 设置速度的先验因子
  // 对应到上图中连接到变量v0的一元因子
  // 这里设置初始速度为0：Vector3(0,0,0)
  typedef Eigen::Matrix<double,-1,1> VectorXd; 

  gtsam::Vector n_velocity(3);// typedef Eigen::VectorXd Vector;gtsam里重写的类型 gtsam中的Vector.h文件中书写的内容
  auto velnoise = noiseModel::Diagonal::Sigmas(Vector3(0.01, 0.01, 0.01));
  PriorFactor<Vector> velprior(V(0),Vector3(0,0,0), velnoise);
  // PriorFactor<Vector> velprior(V(0), Vector3(0,0,0), velnoise);
  newgraph.push_back(velprior); // 将速度v0的初始值加入初始估计集合
  // initialEstimate.insert(V(0), Vector3(0,0,0));
  initialEstimate.insert(V(0),n_velocity);

  // 设置IMU预积分器
  PreintegratedImuMeasurements accum(params);

  // 模仿机器人在运动，这里一共有3个位姿节点0,1,2
  // 在运动过程中模拟IMU预积分，并将IMU因子、IMU偏差因子加入因子图中
  // initialEstimate.print("before for----------------");
  for (size_t i = 0; i < 3; ++i) 
  {
          double t = i * delta_t;
          if (i >0) 
          { 
           // 设置位姿的初始值,这里是错误示范，使用真值作为初始值设置
           // 实际不应该是真值,因为得不到
            auto pose_i = scenario.pose(t); // 返回的式pose3类型数据
            cout<<"第"<<i<<"个数值="<<pose_i<<endl;
            initialEstimate.insert(X(i), pose_i);
          }
          initialEstimate.print("in for----------------");
          // 添加IMU因子和IMU偏差因子
        if (i > 0) 
        {
                // 周期性添加IMU的偏差因子；IMU的偏差需要用其他方式计算，也可以使用离线标定的参数（一般不会）
                if (i % 2 == 0) {
                  //取余数的操作是必须的
                      // ① 避免重复添加key值导致,gtsam报错
                      // ② 增加软件的运行效率,不必遍历下面的循环内容
                  // b1是上一次的IMU偏差变量的键值；b2是本次IMU偏差的键值
                  // biasKey++;                             // 原来的代码
                  // Symbol b1 = biasKey - 1; // 原来的代码
                  // Symbol b2 = biasKey;       // 原来的代码
                  // 按照下面的写法会更加容易理解一些
                  // 为什么要按照下面的内容去写,并不是为了添加图优化的顶点,而是为了告诉约束边链接的都是哪些顶点
                  cout<<"cut in 取余--------------------------------"<<endl;
                  Symbol b0 = biasKey ;
                  Symbol b1 = biasKey+1; 
                  // 添加两个IMU偏差变量之间的二元因子
                  Vector6 covvec;
                  covvec << 0.1, 0.1, 0.1, 0.1, 0.1, 0.1;
                  auto cov = noiseModel::Diagonal::Variances(covvec);
                  // auto f = std::make_shared<BetweenFactor<imuBias::ConstantBias>>(b1, b2, imuBias::ConstantBias(), cov);
                  // newgraph.add(f);
                  cout<<"------------------------------------------before end--"<<endl;
                  newgraph.add(BetweenFactor<imuBias::ConstantBias>(b0, b1, imuBias::ConstantBias(), cov));
                  // 将当前的IMU偏差变量的初始估计加入初始值集合
                  cout<<"insert b1"<<endl;
                  initialEstimate.insert(b1, imuBias::ConstantBias());
                  initialEstimate.print("end in if----------------");
                }
                // 这部分才是预积分器进行积分的地方
                // 每次积分接收加速度、角速度以及间隔时间delta_t
                Vector3 measuredAcc = scenario.acceleration_b(t);// t分别等于1,2,3
                cout<<"--------------------------measuredAcc="<<measuredAcc<<endl;
                Vector3 measuredOmega = scenario.omega_b(t);
                cout<<"--------------------------measuredOmega="<<measuredOmega<<endl;
                accum.integrateMeasurement(measuredAcc, measuredOmega, delta_t);
                /**
                 * Add a single IMU measurement to the preintegration.
                 * @param measuredAcc Measured acceleration (in body frame, as given by the sensor)
                 * @param measuredOmega Measured angular velocity (as given by the sensor)
                 * @param dt Time interval between this and the last IMU measurement
                 */
                // 使用预积分器构建IMU因子，并加入因子图中
                // IMU因子需要指定本次积分的过程连接了哪两个位姿X，速度V以及当前的偏差估计，因此也叫`5-way factor`
                ImuFactor imufac(X(i - 1), V(i - 1), X(i), V(i), biasKey, accum);
                newgraph.add(imufac);
                cout<<"-----------------linear_velocity_vector="<<linear_velocity_vector<<endl;
                // 将速度的初始值加入初始值集合，注意，这里加入的是GroundTruth的速度，只是为了做示例
                initialEstimate.insert(V(i), linear_velocity_vector);
                initialEstimate.print("end ----------------");
                accum.resetIntegration();// 重置IMU预积分器 Re-initialize PreintegratedIMUMeasurements. 
      }
          isam.update(newgraph, initialEstimate);
          result = isam.calculateEstimate();

          newgraph = NonlinearFactorGraph();
          // 这个不加也是可以的?不是已经将整个图的顶点和边在下面清空了嘛?为什么还需要这一步,是不是有所重复
          initialEstimate.print("***********************ImuFactorsExample2_Simple end  It initialEstimate=");
          newgraph.resize(0);
          initialEstimate.clear();// 如果在增量式方法进行优化的方法,清空顶点1行代码被注销,将导致程序报错
          // 上面2行会将之前的数据清空
          // Clear the factor graph and values for the next iteration
          // 特别重要，update以后，清空原来的约束。已经加入到isam2的那些会用bayes tree保管，你不用操心了
          // (上面2行引用自贺一家博士的注释 见:  https://heyijia.blog.csdn.net/article/details/53367268?spm=1001.2014.3001.5502
  }
  // 使用初始值保存因子图
  ofstream file;
  file.open("file.dot");
  string name("filedemo");
  newgraph.saveGraph(file, initialEstimate);//Write the graph in GraphViz format for visualization. 
  // // 打印到命令行
  // newgraph.dot(cout, result);

  // GTSAM_PRINT(result);//最后打印输出内容
  return 0;
}

      
      /*
         const char* ValuesIncorrectType::what() const noexcept {
     if(message_.empty()) {
       std::string storedTypeName = demangle(storedTypeId_.name());
       std::string requestedTypeName = demangle(requestedTypeId_.name());
 
       if (storedTypeName == requestedTypeName) {
         message_ = "WARNING: Detected types with same name but different `typeid`. \
           This is usually caused by incorrect linking/inlining settings when compiling libraries using GTSAM. \
           If you are a user, please report to the author of the library using GTSAM. \
           If you are a package maintainer, please consult `cmake/GtsamPybindWrap.cmake`, line 74 for details.";
       } else {
         message_ =
         "Attempting to retrieve value with key \"" + DefaultKeyFormatter(key_) + "\", type stored in Values is " +
          storedTypeName + " but requested type was " + requestedTypeName;
       }
     }
     return message_.c_str();
   }
 */
/* ************************************************************************* */
