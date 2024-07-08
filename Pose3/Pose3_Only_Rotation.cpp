
#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/Pose2.h>
#include<gtsam/navigation/ImuBias.h>
#include <iostream>
#include<gtsam/navigation/NavState.h>
int main(int argc, char** argv) {
// 下面是A旋转45度
gtsam::Pose3 A =gtsam::Pose3(gtsam::Rot3(0.9238, 0, 0, 0.3826), gtsam::Point3(0, 0, 0));
// 下面是B旋转45度
gtsam::Pose3 B =gtsam::Pose3(gtsam::Rot3(0.9238, 0, 0, 0.3826), gtsam::Point3(0, 0, 0));

  auto com  = A.compose(B);
  auto betw = A.between(B);
  std::cout << "A.compose(B)="<<com << std::endl;
  std::cout << "A.between(B)="<<betw << std::endl;
  //  通过下面网站进行验证旋转后得到，和预期是一致的
  // https://www.andre-gaschler.com/rotationconverter/
  
  return 0;
}
