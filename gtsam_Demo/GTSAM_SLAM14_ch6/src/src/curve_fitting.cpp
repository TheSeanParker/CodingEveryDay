#include <gtsam/nonlinear/DoglegOptimizer.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/inference/Symbol.h>
#include <random>

/*
使用gtsam库实现一个曲线拟合，曲线方程为y = exp(ax^2+bx+c)
*/

double function(const gtsam::Vector3 &param, const double x) {
  return std::exp(param(0) * x * x + param(1) * x + param(2));
}

class CurveFactor : public gtsam::NoiseModelFactor1<gtsam::Vector3> {
public:
  CurveFactor(gtsam::Key key, double x, double y) : gtsam::NoiseModelFactor1<gtsam::Vector3>(), x_(x), y_(y) {
    keys_.push_back(key);
  }

  CurveFactor(gtsam::Key key, gtsam::SharedNoiseModel noise, double x, double y) : gtsam::NoiseModelFactor1<gtsam::Vector3>(noise, key), x_(x), y_(y) {}

  gtsam::Vector evaluateError(const gtsam::Vector3 &param, boost::optional<gtsam::Matrix &> H = boost::none) const {
    double val = function(param, x_);
    if (H) {
      gtsam::Matrix J = gtsam::Matrix::Zero(1, 3);
      J << val * x_ * x_, val * x_, val;
      (*H) = J;
    }
    
    return gtsam::Vector1(val - y_);
  }
  
private:
  double x_, y_;
};

int main(){

  using gtsam::symbol_shorthand::X;
  const double sigma = 1.0;
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::normal_distribution<double> distribution(0.0, sigma);

  gtsam::NonlinearFactorGraph graph;
  const gtsam::Vector3 gt_param(1.0, 2.0, 1.0);

  for (int i = 0; i < 100; ++i) {
    double x = i / 100.0;
    double y = function(gt_param, x) + distribution(generator);

    //? 这里发现是否给观测加噪声，结果有区别
    // graph.emplace_shared<CurveFactor>(X(0), x, y);

    auto noise = gtsam::noiseModel::Isotropic::Sigma(1, sigma);
    graph.emplace_shared<CurveFactor>(X(0), noise, x, y);
  }

  gtsam::Values initial;
  initial.insert(X(0), gtsam::Vector3(1.0, -1.0, 5.0));

  gtsam::GaussNewtonOptimizer optimizer(graph, initial);
//   gtsam::DoglegOptimizer optimizer(graph, initial);
//   gtsam::LevenbergMarquardtOptimizer optimizer(graph, initial);

  std::cout << "\ninit error = " << graph.error(initial) << std::endl;
  auto result = optimizer.optimize();
  std::cout << "final error = " << graph.error(result) << std::endl;
  std::cout << "gt_param = " << gt_param.transpose() << std::endl;
  std::cout << "result = " << result.at<gtsam::Vector3>(X(0)).transpose() << std::endl;
  return 0;
}