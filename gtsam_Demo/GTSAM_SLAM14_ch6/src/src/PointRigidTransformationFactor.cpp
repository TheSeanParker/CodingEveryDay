
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/geometry/Rot3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/base/Matrix.h>
#include <gtsam/base/Vector.h>
#include <vector>
#include <map>

#include <gtsam/base/Vector.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/DoglegOptimizer.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/inference/Key.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/Values.h>
#include <opencv2/core/core.hpp>
#include <random>
#include <cmath>
#include <gtsam/nonlinear/NonlinearOptimizerParams.h>
#include <iostream>
#include "matplotlibcpp.h"

using namespace gtsam;
using namespace std;

    class PointRigidTransformationFactor: public NoiseModelFactor1<gtsam::Pose3>
    {
        public:
            PointRigidTransformationFactor(Key key,const std::vector<gtsam::Point3> &P,const std::vector<gtsam::Point3>&Q,const SharedNoiseModel &noise_model):
                NoiseModelFactor1(noise_model,key),P_(P),Q_(Q) { }            
            virtual ~PointRigidTransformationFactor()
            {   }

             gtsam::Vector evaluateError(const Pose3& T, boost::optional<gtsam::Matrix&> H = boost::none)const 
            {
                gtsam::Matrix A = gtsam::Matrix::Zero(P_.size() * 3,6);
                gtsam::Vector error = gtsam::Vector::Zero(P_.size() * 3);
                for(int i = 0;i < P_.size(); ++i)
                {
                    gtsam::Matrix36 A_i;
                    const Point3 Q_i = T.transformFrom(P_[i],A_i);
                    gtsam::Point3 error_i = Q_i - Q_[i];
                    error.segment(3 * i,3) = error_i;
                    A.block(3 * i,0,3,6) = A_i;
                }
                if(H)
                {
                    *H = A;
                }
                return error;
            }

        private:
            std::vector<gtsam::Point3> P_;
            std::vector<gtsam::Point3> Q_;
    };

    int main(int argc, char const *argv[])
    {
        /* code */
           gtsam::NonlinearFactorGraph graph;
           const gtsam::Key key = gtsam::symbol_shorthand::X(0);
           gtsam::Values initial;
           initial.insert(key,gtsam::Pose3());
           
           cv::RNG rng;
           std::vector<gtsam::Point3> P,Q;
           int inum=100;
           std::vector<double> x_data(inum), y_data(inum);// 为了绘制图像
           for (size_t i = 0; i < inum; i++)
           {
              double mx=i/(inum*1.0);
              double my=-mx*mx;
              double mz=my;
              gtsam::Point3 P_temp{mx,my,mz};//下面是表达旋转
              
              P.push_back(P_temp);
              double mx_obs=i/(inum*1.0)+rng.gaussian(0.05);
              double my_obs=-mx*mx+rng.gaussian(0.03);
              double mz_obs=my+3;
              x_data.push_back(mx_obs);
              y_data.push_back(my_obs);
              gtsam::Point3 Q_temp{mx_obs,my_obs,mz_obs};
              Q.push_back(Q_temp);              
           }
           gtsam::SharedNoiseModel noise_model = gtsam::noiseModel::Isotropic::Sigma(3 * P.size(), 1);
           graph.emplace_shared<PointRigidTransformationFactor>(key,P,Q,noise_model);
            gtsam::GaussNewtonParams params_gn;
            gtsam::GaussNewtonOptimizer optimizer(graph,initial,params_gn);
            const gtsam::Values optimized = optimizer.optimize();
            gtsam::Pose3 T = optimized.at<gtsam::Pose3>(key);
            std::cout<<"output translation="<<T.translation()<<std::endl;
 /************* 绘制曲线************************/
 namespace plt = matplotlibcpp;
    std::vector<double> x(inum), y(inum);
    for (int i = 0; i < inum; ++i)
    {
        x.at(i) = i * 1.0 / inum;
        y.at(i) =-x.at(i)*x.at(i);
    }
    plt::figure_size(640, 480);

    plt::plot(x_data, y_data, "ro");
    plt::plot(x, y, {{"color", "blue"}, {"label", "$y }$"}});
    plt::show();

        return 0;
    }
