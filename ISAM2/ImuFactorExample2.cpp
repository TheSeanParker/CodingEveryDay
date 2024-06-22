/**
 * @file ImuFactorExample2
 * @brief Test example for using GTSAM ImuFactor and ImuCombinedFactor with ISAM2. Simplify and add graphviz by Zeal
 * @author Robert Truax
 * 
 */
#include <gtsam/geometry/SimpleCamera.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/navigation/Scenario.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>
#include <vector>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
using namespace std;
using namespace gtsam;

// Shorthand for velocity and pose variables
using symbol_shorthand::V;
using symbol_shorthand::X;

const double kGravity = 9.81;
/* ************************************************************************* */
int main(int argc, char* argv[]) {
  // 下面设置预积分器的噪声参数,这些噪声参数一般来自IMU的离线标定结果
  auto params = PreintegrationParams::MakeSharedU(kGravity);
  params->setAccelerometerCovariance(I_3x3 * 0.1);
  params->setGyroscopeCovariance(I_3x3 * 0.1);
  params->setIntegrationCovariance(I_3x3 * 0.1);
  params->setUse2ndOrderCoriolis(false);
  params->setOmegaCoriolis(Vector3(0, 0, 0));

  Pose3 delta(Rot3::Rodrigues(-0.1, 0.2, 0.25), Point3(0.05, -0.10, 0.20)); // 微小的位姿变换

  // Start with a camera on x-axis looking at origin
  double radius = 30;
  const Point3 up(0, 0, 1), target(0, 0, 0);
  const Point3 position(radius, 0, 0);
  const SimpleCamera camera = SimpleCamera::Lookat(position, target, up);
  const auto pose_0 = camera.pose();

  // Now, create a constant-twist scenario that makes the camera orbit the
  // origin
  double angular_velocity = M_PI,  // rad/sec
                  delta_t = 1.0 / 18;                 // makes for 10 degrees per step
  Vector3 angular_velocity_vector(0, -angular_velocity, 0);
  Vector3 linear_velocity_vector(radius * angular_velocity, 0, 0);
  auto scenario = ConstantTwistScenario(angular_velocity_vector,linear_velocity_vector, pose_0);

  // Create a factor graph
  NonlinearFactorGraph newgraph;

  // Create (incremental) ISAM2 solver
  ISAM2 isam;

  // Create the initial estimate to the solution
  // Intentionally initialize the variables off from the ground truth
  Values initialEstimate, totalEstimate, result;

  // Add a prior on pose x0. This indirectly specifies where the origin is.
  // 下面是表达噪声的大小
  // 0.1 rad std on roll, pitch, yaw, 
  // 30cm   std on x,y,z.
  // 下面的本质也是预积分,只不过是对顶点进行积分(1)
  Key PriorKey = Symbol('x', 0);
  auto noise = noiseModel::Diagonal::Sigmas((Vector(6) << Vector3::Constant(0.1), Vector3::Constant(0.3)).finished());
  newgraph.push_back(PriorFactor<Pose3>(PriorKey, pose_0, noise));
                                             //PriorFactor (Key key, const VALUE &prior, const SharedNoiseModel &model=nullptr);

  //  Add imu priors
  // 下面的这个定义比较好
  // 下面的本质是预积分,只不过是对顶点进行预积分(2)
  Key biasKey = Symbol('b', 0);
  auto biasnoise = noiseModel::Diagonal::Sigmas(Vector6::Constant(0.1));
  PriorFactor<imuBias::ConstantBias> biasprior(biasKey, imuBias::ConstantBias(),biasnoise);

  // 设置IMU偏差的先验因子
  // 对应到上图中连接到变量b0的一元因子
  newgraph.push_back(biasprior);
  initialEstimate.insert(biasKey, imuBias::ConstantBias());
  
  // 设置速度的先验因子
  // 对应到上图
  // 这里设置初始速度为Vector3(0,0,0)
  auto velnoise = noiseModel::Diagonal::Sigmas(Vector3(0.1, 0.1, 0.1));
  Vector n_velocity(3);
  cout<<"n_velocity="<<n_velocity<<endl;
  n_velocity << 0, angular_velocity * radius, 0;
  Key Velprior_Key = Symbol('v', 0);
  // inline Key V(std::uint64_t j) { return Symbol('v', j); }
  PriorFactor<Vector> velprior(Velprior_Key, n_velocity, velnoise);
  newgraph.push_back(velprior);  // push_back()的内容是Key和Value的结合体组合成map类型的Values
  initialEstimate.insert(Velprior_Key, n_velocity);

  // IMU preintegrator 设置IMU预积分器
  PreintegratedImuMeasurements accum(params);

  // Simulate poses and imu measurements, adding them to the factor graph
  // 仿真机器人在运动,这里一共有3个位姿节点,0,1,2

  for (size_t i = 0; i < 36; ++i) {
    double t = i * delta_t;
    if (i == 0) {  // First time add two poses
      auto pose_1 = scenario.pose(delta_t);
      initialEstimate.insert(X(0), pose_0.compose(delta));
      initialEstimate.insert(X(1), pose_1.compose(delta));
    } 
    else if (i >= 2) {  // Add more poses as necessary
      auto pose_i = scenario.pose(t);
      initialEstimate.insert(X(i), pose_i.compose(delta));
    }

    if (i > 0) {
      // Add Bias variables periodically周期性的添加
      if (i % 5 == 0) {
        biasKey++;
        Symbol b1 = biasKey - 1; // 健值还可以这样运算
        Symbol b2 = biasKey;
        Vector6 covvec;
        covvec << 0.1, 0.1, 0.1, 0.1, 0.1, 0.1;
        auto cov = noiseModel::Diagonal::Variances(covvec);
        auto f = boost::make_shared<BetweenFactor<imuBias::ConstantBias>>(b1, b2, imuBias::ConstantBias(), cov);
        newgraph.add(f);
        initialEstimate.insert(biasKey, imuBias::ConstantBias());
      }
      // Predict acceleration and gyro measurements in (actual) body frame
      Vector3 measuredAcc = scenario.acceleration_b(t) -scenario.rotation(t).transpose()*params->n_gravity;
      Vector3 measuredOmega = scenario.omega_b(t);
      accum.integrateMeasurement(measuredAcc, measuredOmega, delta_t);

      // Add Imu Factor
      ImuFactor imufac(X(i - 1), V(i - 1), X(i), V(i), biasKey, accum);
      newgraph.add(imufac);

      // insert new velocity, which is wrong
      initialEstimate.insert(V(i), n_velocity);
      accum.resetIntegration();//	Re-initialize PreintegratedIMUMeasurements. 
    }

    // Incremental solution
    // isam.update(newgraph, initialEstimate);
    // result = isam.calculateEstimate();
    // newgraph = NonlinearFactorGraph();
    // initialEstimate.clear();
  }
  result = LevenbergMarquardtOptimizer(newgraph, initialEstimate).optimize();
  cout<<"---------------LevenbergMarquardtOptimizer"<<endl;
  GTSAM_PRINT(result);//最后打印输出内容
  return 0;
}
//v0   ->   N5Eigen6MatrixIdLin1ELi1ELi0ELin1ELi1EEE
//               N5gtsam12GenericValueIN5Eigen6MatrixIdLi3ELi1ELi0ELi3ELi1EEEE
//               N5Eigen6MatrixIdLin1ELi1ELi0ELin1ELi1EEE
/* ************************************************************************* */
