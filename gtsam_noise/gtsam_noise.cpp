
#include <iostream>
#include<gtsam/navigation/ImuBias.h>
#include<gtsam/linear/NoiseModel.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/inference/Symbol.h>

using namespace gtsam;
using namespace std;
using symbol_shorthand::B;

int main(int argc, char** argv) { 
  gtsam::noiseModel::Diagonal::shared_ptr priorBiasNoise;
  priorBiasNoise  = gtsam::noiseModel::Isotropic::Sigma(6, 1e-3); // 1e-2 ~ 1e-3 seems to be good
  cout<<"print priorBiasNoise=\n"<<(*priorBiasNoise).R()<<endl;  
  cout<<"print sigmas()=\n"<<(*priorBiasNoise).sigmas()<<endl;  
  gtsam::imuBias::ConstantBias prevBias_;
  prevBias_ = gtsam::imuBias::ConstantBias();
  cout<<"print prevBias_="<<  prevBias_<<endl;
  gtsam::PriorFactor<gtsam::imuBias::ConstantBias> priorBias(B(0), prevBias_, priorBiasNoise);

  gtsam::noiseModel::Diagonal::shared_ptr correctionNoise;
  correctionNoise = gtsam::noiseModel::Diagonal::Sigmas((gtsam::Vector(6) << 0.05, 0.05, 0.05, 0.1, 0.1, 0.1).finished()); // rad,rad,rad,m, m, m
  cout<<"print correctionNoise=\n"<<(*correctionNoise).R()<<endl;  
  return 0;
}
