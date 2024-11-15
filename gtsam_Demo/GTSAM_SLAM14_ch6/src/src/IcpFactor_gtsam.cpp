#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Pose3.h>
#include <iostream>
using namespace gtsam;
using namespace std;
using namespace Eigen;

class IcpFactor : public NoiseModelFactor1<Pose3>
{
public:
/**
 * @brief Construct a new Icp Factor object
 * @param noiseModel
 * @param key
 * @param measurement
 * @param p
 */
IcpFactor(const SharedNoiseModel& noiseModel, Key key,const Point3& measurement, const Point3& p) : NoiseModelFactor1(noiseModel, key), measurement_(measurement), p_(p){} //列表初始化里,也可调用其他库的函数                                                                                                                                                                                                               
            Vector evaluateError(const Pose3& T, boost::optional<gtsam::Matrix&> H = boost::none) const 
            // 这里H是出现在gtsam库的哪个里面的?
            // 这个函数居然运行进去了，因为是Override，所以应该是一种对原函数的重写
            // 关注一下H矩阵,参数boost::none是一个类似空指针的none_t类型常量，表示未初始化
            {
                // construct prediction and compute jacobian
                gtsam::Matrix36 Hpose;
                const Point3    prediction = T.transformFrom(p_, Hpose);// Hpose 是雅各比
                if (H)
                {
                        *H = Hpose;
                }
                return prediction - measurement_;
            }
private:
Point3 measurement_;
Point3 p_;
};

struct PairedPoint
{
    Point3 p;
    Point3 q;
    PairedPoint(const Point3& _p, const Point3& _q) : p(_p), q(_q)// 列表初始化
    {
    }
};
std::vector<PairedPoint> generatePairedPoints(const Pose3& T)// 生成匹配的点对,然后将生成的点对放入到对应的容器里
{
    std::vector<PairedPoint> data;
    // create an unit cube, centered on (0, 0, 0)
    Point3 vertices[] = {{-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5},
                                           {0.5, 0.5, -0.5},    {-0.5, 0.5, -0.5},
                                           {-0.5, -0.5, 0.5},   {0.5, -0.5, 0.5},
                                           {0.5, 0.5, 0.5},      {-0.5, 0.5, 0.5}};
    for (size_t i = 0; i < 8; i++)
    {
        data.emplace_back(vertices[i], T.transformFrom(vertices[i]));
        // 将旋转前的点和旋转后的点都加入到容器中去,顺便求出雅克比,?谁对谁的雅克比?应该是残差对pose的雅克比
    }
    return data;
}

int main(int argc, char const *argv[])
{  // ground truth transformation
    const Pose3 T(Rot3::RzRyRx(0.2, -0.1, 0.05), Point3(0.5, 0.3, -0.2));//前面是旋转,后面是平移,最后形成了位姿
    // generate a bunch of 3d points
    std::vector<PairedPoint> data = generatePairedPoints(T);   // 虚拟仿真成匹配好的点对,因为两帧之间是严格按照固定T进行旋转的,所以误差为0
    // construct noise model
    SharedNoiseModel model = noiseModel::Isotropic::Sigma(3, 0.01);// 噪声数据服从正态分布,参数分别是均值和方差// 且本质上为shared_ptr

    // construct pose key
    const Key vertex = symbol_shorthand::X(0);// shorthand 简略表达,表达因子的名称,X0,X1,X2
    //键值主要目的是为了让因子图指定该因子连接到哪些变量中去,健值不一定是连续的,但一定要是唯一的
    //如果有第2个变量
    //const Key key = symbol_shorthand::X(1)
    //   Symbol key('x',1);
    // build factor graph
    NonlinearFactorGraph graph;
    // boost::shared_ptr<ResectioningFactor> factor;
    for (const auto& m : data)
    {
        /*
        m.q测量值
        m.p噪声模型
        */
        graph.emplace_shared<IcpFactor>(model, vertex, m.q, m.p);
        //    旋转前是p,旋转后是q;里面的参数的顺序是由IcpFactor()函数确定的,可以进行调整,并非固定的
        //   graph.push_back(factor);
    };
    // set initial values
    Values initial;
    initial.print("set initial value\n");

    boost::optional<Matrix36> H = boost::none;// 一个很小的数值,几乎就是为0
    Matrix36 a;
    a<<1,1,2,2,3,3,
           4,4,1,1,1,1,
           3,3,3,3,3,3;
    H =a;
    // Rot3 R_;
    // Matrix3 R = R_.matrix();
    // cout<<"output  R=\n"<<(R)<<endl;//就是单位矩阵
    // cout<<"output  Pose3::identity()=\n"<<(Pose3::identity())<<endl;//R+t
    // cout<<"output  Pose3=\n"<<(Pose3())<<endl;
    cout<<"****output  H=\n"<<(*H)*2<<endl;
    // cout<<"(H->leftCols<3>())=\n"<<(H->leftCols<3>())<<endl;
    // gtsam::Matrix36 Hpose;
    // cout<<"output  Hpose=\n"<<(Hpose)<<endl;//也是一个很小的数值,几乎为0
              if(H)//当矩阵为0的时候,不进入到下面的函数里
            {
                cout<<"*************boost::optional<Matrix36> H = boost::none*****************"<<endl;
            }
    initial.insert(vertex, Pose3::identity());
    // 优化前位姿的初始值,是李群位姿4*6的矩阵
    // 如果有多个因子的话,就向下添加,例如
    // initial.insert(X1,gtsam::Pose3(初始位置和姿态))
    // Pose3表示3维位姿,Pose2表示2维姿态
    // optimize
    GaussNewtonParams parameters;//参数对象
    parameters.relativeErrorTol = 1e-9; // 迭代变化量小于这个值就退出
    parameters.maxIterations = 100; //最大迭代次数
    //创建一个高斯牛顿优化器 arg：      因子图 初值              参数对象
    GaussNewtonOptimizer optimizer(graph, initial, parameters);
    //求出优化解 得到变量的最优值
    const Values result = optimizer.optimize();

    // const Values result =GaussNewtonOptimizer(graph, initial /*default parameters*/).optimize();
    std::cout << "ground truth = " << T << "\n";
    std::cout << "   estimated = " << result.at<Pose3>(vertex) << std::endl;
     std::cout << "parameters.iterativeParams = " <<parameters.iterativeParams<<std::endl;
    result.print("final result\n");
    return 0;
}
