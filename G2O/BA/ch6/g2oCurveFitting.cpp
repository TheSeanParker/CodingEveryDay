#include <iostream>
#include <g2o/core/g2o_core_api.h>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/core/optimization_algorithm_dogleg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <Eigen/Core>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <chrono>
#include <g2o/types/slam3d/se3quat.h>
using namespace std;

// 曲线模型的顶点，模板参数：优化变量维度和数据类型
class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d> {
  public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW //这个宏就是运算符new的对齐版本重载。
  // 重置
  virtual void setToOriginImpl() override {
    // // _estimate << 0, 0, 0;
    // _estimate.fill(100000000000);
  }
  // 顶点更新函数,如果是矩阵旋转,需要用李群李代数去表达旋转
  virtual void oplusImpl(const double *update) override //implementation实现
  {
    _estimate += Eigen::Vector3d(update);
  }
  // 存盘和读盘：留空
  virtual bool read(istream &in) {}
  virtual bool write(ostream &out) const {}
};
// 误差模型 模板参数：观测值维度，类型，连接顶点类型
class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex> {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  CurveFittingEdge(double x) : BaseUnaryEdge(), _x(x){};
  
  // 计算曲线模型误差
  virtual void computeError() override 
  {
  const CurveFittingVertex *v = static_cast<const CurveFittingVertex *> (_vertices[0]);// 此步骤是固定写法么?,还可以增加_vertices[1]到n
  const Eigen::Vector3d abc = v->estimate();
  _error(0, 0) = _measurement - std::exp(abc(0) * _x * _x + abc(1) * _x + abc(2));// 进去了好几次
              //误差=测量值-估计值
  }

  // 手动计算雅可比矩阵
  virtual void linearizeOplus() override 
  {
    const CurveFittingVertex *v = static_cast<const CurveFittingVertex *> (_vertices[0] );//曾祖类转换到子类
    // VertexContainer _vertices;
    // typedef std::vector<g2o::HyperGraph::Vertex *> g2o::HyperGraph::VertexContainer
    const Eigen::Vector3d abc = v->estimate();
    double y = exp(abc[0] * _x * _x + abc[1] * _x + abc[2]);// 中间变量
    _jacobianOplusXi[0] = -_x * _x * y;
    _jacobianOplusXi[1] = -_x * y;
    _jacobianOplusXi[2] = -y;
  }
  virtual bool read(istream &in) {}
  virtual bool write(ostream &out) const {}
  public:
  double _x;  // x 值， y 值为 _measurement
};

g2o::SE3Quat toSE3Quat(const Eigen::Matrix4d &cvT)
{
    Eigen::Matrix<double, 3, 3> R = cvT.block<3, 3>(0, 0);
    Eigen::Matrix<double, 3, 1> t = cvT.block<3, 1>(0, 3);
    return g2o::SE3Quat(R, t);
}

int main(int argc, char **argv) 
{
 Eigen::Matrix4d T1;
  T1<<1,0,0,1,
            0,1,0,2,
            0,0,1,3,
            0,0,0,1;
  g2o::SE3Quat aa= toSE3Quat(T1);
  std::cout<<"aa.log()="<<aa.log()<<std::endl;
  // 数据生成部分
  double ar = 1.0, br = 2.0, cr = 1.0;            // 真实参数值
  double ae = 2.0, be = -1.0, ce = 5.0;        // 估计参数值  (估计的初始值,如果偏差比较大,需迭代次数比较多,才能迭代到确定的结果数值)
  int N = 100;                                                      // 数据点
  double w_sigma = 1.0;                               // 噪声Sigma值
  double inv_sigma = 1.0 / w_sigma;
  cv::RNG rng;                                                    // OpenCV随机数产生器

  vector<double> x_data, y_data;             // 数据
  for (int i = 0; i < N; i++) 
  {
    double x = i / 100.0;
    x_data.push_back(x);
    y_data.push_back(exp(ar * x * x + br * x + cr) + rng.gaussian(w_sigma * w_sigma));// 真实值+噪声=形成了所谓的真实数据
  }

  typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;  // 每个误差项优化变量维度为3，误差值维度为1
  typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType; // 线性求解器类型
  //typedef typename Traits::PoseMatrixType PoseMatrixType; 涉及到了模板???需要学习模板知识in bolck_solver.h文件中

  // 梯度下降方法，可以从GN, LM, DogLeg 中选  
  auto solver = new g2o::OptimizationAlgorithmGaussNewton(g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));
  // // ?? 此部分先要学习组合设计模式中的树节点和叶子节点,以及他们之间的区别???
  g2o::SparseOptimizer optimizer;     // 稀疏优化图模型
  optimizer.setAlgorithm(solver);       // 设置求解器
  optimizer.setVerbose(true);               // 打开调试输出
    // 如果这个数很大，说明此边的值与其他边很不相符
    // 往图中增加顶点
  CurveFittingVertex *v = new CurveFittingVertex();
  v->setEstimate(Eigen::Vector3d(ae, be, ce));
    // 调整顶点,只有顶点调节使得整体误差最小的时候,才是最优的状态
    //设定估计参数每次迭代的初始值,因为是单节点,所以只运行一次
    // 类的指针,然后可以调用这个类的成员函数,但是CurveFittingVertex是继承自BaseVertex类,所以本质上是BaseVertex类的成员函数
  v->setId(0);//setId()函数是BaseVertex类的上一层的父类,继承了2个父类 Vertex : public HyperGraph::Vertex, public HyperGraph::DataContainer
  optimizer.addVertex(v);

  // 往图中增加边,这里面的N值表示着实际观测到点的数量
  // 下面很多的成员函数,基本留了对外的接口,实现细节基本都在类里实现的
  for (int i = 0; i < N; i++) 
  {
    CurveFittingEdge *edge = new CurveFittingEdge(x_data[i]);
    edge->setId(i);
    edge->setVertex(0, v);// 设置连接的顶点,为什么前面是0,说明它连接顶点的编号是0,若再设置边连接的顶点是edge->setVertex(1,)
    edge->setMeasurement(y_data[i]);      // 观测数值
    edge->setInformation(Eigen::Matrix<double, 1, 1>::Identity() * 1/ (w_sigma * w_sigma)); // 信息矩阵：协方差矩阵之逆,因为要输入的是Matrix的类型数据!
    optimizer.addEdge(edge);
  }
  // 执行优化
  cout << "start optimization" << endl;
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  optimizer.initializeOptimization();
  optimizer.optimize(10);
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

  // 输出优化值
  Eigen::Vector3d abc_estimate = v->estimate();
  cout << "estimated model: " << abc_estimate.transpose() << endl;

  return 0;
}


