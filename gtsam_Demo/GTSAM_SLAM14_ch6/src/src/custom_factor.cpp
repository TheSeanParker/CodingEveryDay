

#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/geometry/Pose2.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/inference/Key.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/nonlinear/Marginals.h>

using namespace std;
using namespace gtsam;

// 类名 : 继承于NoiseModelFactor1<优化变量类型>
class UnaryFactor : public NoiseModelFactor1<Pose2>
{
    // 观测值(x,y),当然也可以采用Point2
    double mx_, my_;

public:
    // 需要重写这个函数来定义误差和雅可比矩阵
    using NoiseModelFactor1<Pose2>::evaluateError;

    // 因子的智能指针
    typedef std::shared_ptr<UnaryFactor> shared_ptr;

    // 一元因子的构造函数， (key , 测量值， 噪声模型)
    UnaryFactor(Key j, double x, double y, const SharedNoiseModel &model) : NoiseModelFactor1<Pose2>(model, j), mx_(x), my_(y) {}

    ~UnaryFactor() override {}

    Vector evaluateError(const Pose2 &q, boost::optional<Matrix &> H = boost::none) const override
    {
       
        // 雅可比矩阵，在切空间等于右手定则的旋转矩阵
        // H =  [ cos(q.theta)  -sin(q.theta) 0 ]
        //      [ sin(q.theta)   cos(q.theta) 0 ]
        const Rot2 &R = q.rotation();
        if (H)
        {
            (*H) = (gtsam::Matrix(2, 3) << R.c(), -R.s(), 0.0, R.s(), R.c(), 0.0).finished();
        }

        // 返回误差
        return (Vector(2) << q.x() - mx_, q.y() - my_).finished();
    }

    // The second is a 'clone' function that allows the factor to be copied. Under most
    // circumstances, the following code that employs the default copy constructor should
    // work fine.
    gtsam::NonlinearFactor::shared_ptr clone() const override
    {
        return boost::static_pointer_cast<gtsam::NonlinearFactor>(
            gtsam::NonlinearFactor::shared_ptr(new UnaryFactor(*this)));
    }

}; // UnaryFactor

int main(int argc, char **argv)
{
    // 1. 创建因子图融合，后续加入因子
    NonlinearFactorGraph graph;


    // 2a. 加入里程计因子（二元因子）
    // 里程计因子的噪声模型
    auto odometryNoise = noiseModel::Diagonal::Sigmas(Vector3(0.2, 0.2, 0.1));
    // 创建里程计因子（即二元边因子）
    graph.emplace_shared<BetweenFactor<Pose2>>(1, 2, Pose2(2.0, 0.0, 0.0), odometryNoise);
    graph.emplace_shared<BetweenFactor<Pose2>>(2, 3, Pose2(2.0, 0.0, 0.0), odometryNoise);

    // 2b. 加入自定义的一元因子测量值
    auto unaryNoise = noiseModel::Diagonal::Sigmas(Vector2(0.1, 0.1)); // 其中需要噪声模型维度需要和测量值的维度保持一致，在XY方向标准差为10cm// 10cm std on x,y
    graph.emplace_shared<UnaryFactor>(1, 0.0, 0.0, unaryNoise);
    graph.emplace_shared<UnaryFactor>(2, 2.0, 0.0, unaryNoise);
    graph.emplace_shared<UnaryFactor>(3, 4.0, 0.0, unaryNoise);
    graph.print("\nFactor Graph:\n"); // print


    // 3. 添加变量节点的初始值
    Values initialEstimate;
    initialEstimate.insert(1, Pose2(0.5, 0.0, 0.2));
    initialEstimate.insert(2, Pose2(2.3, 0.1, -0.2));
    initialEstimate.insert(3, Pose2(4.1, 0.1, 0.1));
    initialEstimate.print("\nInitial Estimate:\n"); // print

    // LevenbergMarquardtOptimizer optimizer(graph, initialEstimate);
    // 4. 采用高斯牛顿方法进行优化
    GaussNewtonOptimizer optimizer(graph, initialEstimate);
    Values result = optimizer.optimize();
    result.print("Final Result:\n");

    // 5. 计算并打印所有变量的边际协方差
    Marginals marginals(graph, result);
    cout << "x1 covariance:\n"
         << marginals.marginalCovariance(1) << endl;
    cout << "x2 covariance:\n"
         << marginals.marginalCovariance(2) << endl;
    cout << "x3 covariance:\n"
         << marginals.marginalCovariance(3) << endl;

    return 0;
}
