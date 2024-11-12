
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
#include "matplotlibcpp.h"
#include <cmath>
#include <gtsam/nonlinear/NonlinearOptimizerParams.h>
// https://blog.csdn.net/weixin_41681988/article/details/132001320
using namespace std;
using namespace gtsam;

namespace plt = matplotlibcpp;
// y = exp(a x^2 + b x + c)
// 利用x和参数a,b,c计算y
double funct(const gtsam::Vector3 &p, const double x)
{
    return exp(p(0) * x * x + p(1) * x + p(2));
}

// 自定义类名 : 继承于一元因子类<优化变量的数据类型>
class curvfitFactor : public gtsam::NoiseModelFactor1<gtsam::Vector3>
{
    double mx, my; // 观测值    
public:
    curvfitFactor(gtsam::Key key, const gtsam::SharedNoiseModel &noise, double x, double y)
                              : gtsam::NoiseModelFactor1<gtsam::Vector3>(noise, key), mx(x), my(y){ }
    virtual ~curvfitFactor()
    {
    }

    // 自定义因子一定要重写evaluateError函数(优化变量, 雅可比矩阵)
    gtsam::Vector evaluateError(const gtsam::Vector3 &p, boost::optional<gtsam::Matrix &> H = boost::none) const
    {
        auto val = funct(p, mx);
        if (H) // 残差为1维，优化变量为3维，雅可比矩阵为1*3
        {
            gtsam::Matrix Jac = gtsam::Matrix::Zero(1, 3);
            Jac << mx * mx * val, mx * val, val;
            (*H) = Jac;
        }
        return gtsam::Vector1(val - my); // 返回值为残差
    }
};

int main()
{
    using gtsam::symbol_shorthand::X;
    // const double sig = 1;
    // std::random_device rd;
    // std::default_random_engine generator_(rd());
    // std::normal_distribution<double> noise(0, sig);
    gtsam::NonlinearFactorGraph graph;
    const gtsam::Vector3 para(1.0, 2.0, 1.0); // a,b,c的真实值
    double w_sigma = 1.0;                                    // 噪声Sigma值
    double inv_sigma = 1.0 / w_sigma;
    cv::RNG rng;                                                         // OpenCV随机数产生器
    vector<double> x_data, y_data;
   int inum=100;
    for (int i = 0; i < inum; ++i)
    {
        double mx = i /( inum*1.0);
        auto my = funct(para, mx) + rng.gaussian(w_sigma * w_sigma); // 加入了噪声数据
        auto noiseM = gtsam::noiseModel::Isotropic::Sigma(1, w_sigma); // 噪声的维度需要与观测值维度保持一致
        graph.emplace_shared<curvfitFactor>(X(0), noiseM, mx, my);     // 加入一元因子

        x_data.push_back(mx);
        y_data.push_back(my);
    }
    
    gtsam::Values intial;
    intial.insert<gtsam::Vector3>(X(0), gtsam::Vector3(2.0, -1.0, 5.0));
    gtsam::LevenbergMarquardtParams params;
    params.maxIterations=5;
    // params.relativeErrorTol=450;
    // params.absoluteErrorTol=455;
    params.errorTol=51;
    std::cout << "User required to perform maximum  " << params.maxIterations << " iterations "<< std::endl;
    params.setMaxIterations(8);
    // DoglegOptimizer opt(graph, intial);               // 使用Dogleg优化
    // GaussNewtonOptimizer opt(graph, intial); // 使用高斯牛顿优化
    LevenbergMarquardtOptimizer opt(graph, intial,params); // 使用LM优化
    std::cout << "User required to perform maximum  " << params.maxIterations << " iterations "<< std::endl;
    std::cout << "initial error=" << graph.error(intial) << std::endl;
    // graph.print("graph=");//100个因子，就是100个点参与到运算中去；
    
    double Relaerror=params.getRelativeErrorTol();
    double absoluteError=params.getAbsoluteErrorTol();
 
    opt.iterate();
    opt.print("*********opt2");
    
    int num=opt.getInnerIterations();
    const gtsam::Values res = opt.values();
    std::cout<<"num5="<<num<<std::endl;
    std::cout << "fifth error=" << graph.error(res) << std::endl;
    opt.iterate();
    opt.iterate();
    opt.iterate();
    opt.iterate();
    opt.iterate();
    opt.iterate();
    const gtsam::Values res1 = opt.values();
    num=opt.getInnerIterations();

    std::cout<<"num7="<<num<<std::endl;
    std::cout << "seventh error=" << graph.error(res1) << std::endl;

    opt.print("*********opt2");
    num=opt.getInnerIterations();
    std::cout<<"=======num="<<num<<std::endl;
    // opt.iterate();
    // num=opt.getInnerIterations();
    // std::cout<<"num4="<<num<<std::endl;
    // opt.iterate();
    // num=opt.getInnerIterations();
    // std::cout<<"num5="<<num<<std::endl;
    // opt.iterate();
    // num=opt.getInnerIterations();
    // std::cout<<"num6="<<num<<std::endl;
    // std::cout << "final error=" << graph.error(res) << std::endl;
    gtsam::Vector3 matX0 = res1.at<gtsam::Vector3>(X(0));
    std::cout << "a b c: " << matX0 << "\n";

    /************* 绘制曲线************************/
    int n = 5000;
    std::vector<double> x(n), y(n), w(n, 2);
    for (int i = 0; i < n; ++i)
    {
        x.at(i) = i * 1.0 / n;
        y.at(i) = exp(matX0(0) * x[i] * x[i] + matX0(1) * x[i] + matX0(2));
    }

    plt::figure_size(640, 480);

    plt::plot(x_data, y_data, "ro");
    plt::plot(x, y, {{"color", "blue"}, {"label", "$y = e^{ax^2+bx+c}$"}});

    plt::show();

    return 0;
}
