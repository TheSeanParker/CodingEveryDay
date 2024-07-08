
#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/Pose2.h>
#include<gtsam/navigation/ImuBias.h>
#include <iostream>
#include<gtsam/navigation/NavState.h>
int main(int argc, char** argv) {
// B 的旋转量为绕 x 轴旋转 180 度
//   gtsam::Pose3 B =gtsam::Pose3(gtsam::Rot3(0, 1, 0, 0), gtsam::Point3(1, 2, 0));
  gtsam::Pose3 B =gtsam::Pose3(gtsam::Rot3(1, 0, 0, 0), gtsam::Point3(1, 2, 0));
// A 的旋转量为绕 z 轴旋转 180 度
//   gtsam::Pose3 A =gtsam::Pose3(gtsam::Rot3(0, 0, 0, 1), gtsam::Point3(2, 1, 0));
  gtsam::Pose3 A =gtsam::Pose3(gtsam::Rot3(1, 0, 0, 0), gtsam::Point3(2, 1, 0));
  // gtsam::Pose2 B;
  gtsam::Point3 P3;
  gtsam::Point2 P2;
  auto com  = A.between(B);
  auto betw = A.compose(B);
  std::cout << "A.compose(B)="<<com << std::endl;
  std::cout << "A.between(B)="<<betw << std::endl;
  gtsam::NavState propState_ ;
  float imuAccNoise{3.99};
  gtsam::Matrix3 gyroscopeCovariance=gtsam::Matrix33::Identity(3,3) * pow(imuAccNoise, 2);
  std::cout <<"gyroscopeCovariance="<<gyroscopeCovariance<< std::endl;

  std::cout <<"gtsam::NavState propState_="<< propState_<< std::endl;
  std::cout <<"propState_.attitude()="<< propState_.attitude()<< std::endl;
  std::cout <<"gtsam::imuBias::ConstantBias()="<< gtsam::imuBias::ConstantBias()<< std::endl;
  return 0;
}
