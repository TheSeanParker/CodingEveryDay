#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <Eigen/Core>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/sparse_optimizer.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/solver.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <sophus/se3.hpp>
#include <chrono>

using namespace std;
using namespace cv;

void find_feature_matches(
  const Mat &img_1, const Mat &img_2,
  std::vector<KeyPoint> &keypoints_1,
  std::vector<KeyPoint> &keypoints_2,
  std::vector<DMatch> &matches);

// 像素坐标转相机归一化坐标
Point2d pixel2cam(const Point2d &p, const Mat &K);

// BA by g2o
typedef vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d>> VecVector2d;
typedef vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d>> VecVector3d;
// 声明函数
void bundleAdjustmentG2O(
  const VecVector3d &points_3d,
  const VecVector2d &points_2d,
  const Mat &K,
  Sophus::SE3d &pose
);

// BA by gauss-newton
void bundleAdjustmentGaussNewton(
  const VecVector3d &points_3d,
  const VecVector2d &points_2d,
  const Mat &K,
  Sophus::SE3d &pose
);

int main(int argc, char **argv) {
  // if (argc != 5) //argc 表示输入变量的是5个
  // {
  //   cout << "not input: pose_estimation_3d2d img1 img2 depth1 depth2" << endl;
  //   return 1;
  // }

  cout<<"Sophus::SE3d())=\n"<<(Sophus::SE3d().rotationMatrix())<<endl;
  //-- 读取图像
  Mat img_1 = imread(argv[1]);
  Mat img_2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
  Mat img_3 = imread(argv[3]);
  imshow("Pic1",img_1);
  cv::waitKey(4000);// 4秒
  imshow("Pic2",img_2);
  // cv::waitKey(0);// 等待鼠标的任意键触发
  cv::waitKey(4000);
  imshow("Pic3",img_3);
  cv::waitKey(4000);// 4秒
  assert(img_1.data && img_2.data && "Can not load images!");// asser()为断言函数,如果返回错误则终止程序

  vector<KeyPoint> keypoints_1, keypoints_2;
  vector<DMatch> matches;
  find_feature_matches(img_1, img_2, keypoints_1, keypoints_2, matches);
  cout << "一共找到了" << matches.size() << "组匹配点" << endl;

  // 建立视觉3D点
  Mat d1 = imread(argv[3], CV_LOAD_IMAGE_UNCHANGED);                       // 深度图为16位无符号数，单通道图像
  imshow("d1",d1);
  cv::waitKey(4000);// 4秒
  Mat K = (Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);// 相机内参
  vector<Point3f> pts_3d;
  vector<Point2f> pts_2d;
  for (DMatch m:matches) {
    ushort d = d1.ptr<unsigned short>(int(keypoints_1[m.queryIdx].pt.y))[int(keypoints_1[m.queryIdx].pt.x)];// ?存在疑问的
    // ushort d = d1.ptr<unsignedshort> (row)[column];就是指向d1的第row行的第column个数据。数据类型为无符号的短整型。
    if (d == 0)   // bad depth
      continue;
    float dd = d / 5000.0;//?猜测应该是尺度信息
    Point2d p1 = pixel2cam(keypoints_1[m.queryIdx].pt, K);
    pts_3d.push_back(Point3f(p1.x * dd, p1.y * dd, dd));
    pts_2d.push_back(keypoints_2[m.trainIdx].pt);
  }

  cout << "3d-2d pairs: " << pts_3d.size() << endl;
  cout << "       2d pairs: " << pts_2d.size() << endl;
  //应该和上一行的坐标数量是一致的,find_feature_matches()过后就注定上下两行的特征是经过匹配之后的
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  Mat r, t;

  // 方法1
  // solvePnP(pts_3d, pts_2d, K, Mat(), r, t, false); // 调用OpenCV 的 PnP 求解，可选择EPNP，DLS等方法
  // Mat R;
  // cv::Rodrigues(r, R); // r为旋转向量形式，用Rodrigues公式转换为矩阵
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  // cout << "solve pnp in opencv cost time: " << time_used.count() << " seconds." << endl;

  // cout << "R=" << endl << R << endl;
  // cout << "t=" << endl << t << endl;

// 方法2 下面是手写高斯牛顿法求解矩阵旋转
  VecVector3d pts_3d_eigen;// 分别拿到3维点的坐标
  VecVector2d pts_2d_eigen;// 分别拿到2维点的坐标
  for (size_t i = 0; i < pts_3d.size(); ++i) {
    pts_3d_eigen.push_back(Eigen::Vector3d(pts_3d[i].x, pts_3d[i].y, pts_3d[i].z));//这个显示很清楚 pts_3d是带深度的3维信息
    pts_2d_eigen.push_back(Eigen::Vector2d(pts_2d[i].x, pts_2d[i].y));
  }
  cout << "calling bundle adjustment write by gauss newton" << endl;
  Sophus::SE3d pose_gn;// 单位旋转矩阵,平移向量为0
  t1 = chrono::steady_clock::now();
  bundleAdjustmentGaussNewton(pts_3d_eigen, pts_2d_eigen, K, pose_gn);
  t2 = chrono::steady_clock::now();
  time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "solve pnp by gauss newton cost time: " << time_used.count() << " seconds." << endl;

// 方法3 用g2o来求解优化的问题
  cout << "calling bundle adjustment by g2o" << endl;
  Sophus::SE3d pose_g2o;
  t1 = chrono::steady_clock::now();
  bundleAdjustmentG2O(pts_3d_eigen, pts_2d_eigen, K, pose_g2o);
  t2 = chrono::steady_clock::now();
  time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "solve pnp by g2o cost time: " << time_used.count() << " seconds." << endl;

  return 0;
}

void find_feature_matches(const Mat &img_1, const Mat &img_2,
                          std::vector<KeyPoint> &keypoints_1,
                          std::vector<KeyPoint> &keypoints_2,
                          std::vector<DMatch> &matches) {
  //-- 初始化
  Mat descriptors_1, descriptors_2;
  // used in OpenCV3
  Ptr<FeatureDetector> detector = ORB::create();
  Ptr<DescriptorExtractor> descriptor = ORB::create();
  // use this if you are in OpenCV2
  // Ptr<FeatureDetector> detector = FeatureDetector::create ( "ORB" );
  // Ptr<DescriptorExtractor> descriptor = DescriptorExtractor::create ( "ORB" );
  Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
  //-- 第一步:检测 Oriented FAST 角点位置
  detector->detect(img_1, keypoints_1);
  detector->detect(img_2, keypoints_2);

  //-- 第二步:根据角点位置计算 BRIEF 描述子
  descriptor->compute(img_1, keypoints_1, descriptors_1);
  descriptor->compute(img_2, keypoints_2, descriptors_2);

  //-- 第三步:对两幅图像中的BRIEF描述子进行匹配，使用 Hamming 距离
  vector<DMatch> match;
  // BFMatcher matcher ( NORM_HAMMING );
  matcher->match(descriptors_1, descriptors_2, match);

  //-- 第四步:匹配点对筛选
  double min_dist = 10000, max_dist = 0;

  //找出所有匹配之间的最小距离和最大距离, 即是最相似的和最不相似的两组点之间的距离
  for (int i = 0; i < descriptors_1.rows; i++) {
    double dist = match[i].distance;
    if (dist < min_dist) min_dist = dist;
    if (dist > max_dist) max_dist = dist;
  }

  printf("-- Max dist : %f \n", max_dist);
  printf("-- Min dist : %f \n", min_dist);

  //当描述子之间的距离大于两倍的最小距离时,即认为匹配有误.但有时候最小距离会非常小,设置一个经验值30作为下限.
  for (int i = 0; i < descriptors_1.rows; i++) {
    if (match[i].distance <= max(2 * min_dist, 30.0)) {
      matches.push_back(match[i]);
    }
  }
}

Point2d pixel2cam(const Point2d &p, const Mat &K) {
  return Point2d
    (
      (p.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
      (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1)
    );
}

void bundleAdjustmentGaussNewton(const VecVector3d &points_3d,const VecVector2d &points_2d,const Mat &K,Sophus::SE3d &pose) 
{
  typedef Eigen::Matrix<double, 6, 1> Vector6d;// VectorXd的来历
  const int iterations = 10;
  double cost = 0, lastCost = 0;
  double fx = K.at<double>(0, 0);//openCV里的Mat使用方法
  double fy = K.at<double>(1, 1);
  double cx = K.at<double>(0, 2);
  double cy = K.at<double>(1, 2);

  for (int iter = 0; iter < iterations; iter++) 
  {
          Eigen::Matrix<double, 6, 6> H = Eigen::Matrix<double, 6, 6>::Zero();
          Vector6d b = Vector6d::Zero();

          cost = 0;// 每次的代价函数都要归零
          // compute cost
          for (int i = 0; i < points_3d.size(); i++) 
          {
                  Eigen::Vector3d pc = pose * points_3d[i];//SE3如何与Vector3d相乘,相当于对这个点进行了平移和旋转;T*p=(R*P+t);对某个3维点,依然适用
                  double inv_z = 1.0 / pc[2];
                  double inv_z2 = inv_z * inv_z;
                  Eigen::Vector2d proj(fx * pc[0] / pc[2] + cx, fy * pc[1] / pc[2] + cy);

                  Eigen::Vector2d e = points_2d[i] - proj;// 残差
                  cost += e.squaredNorm();// 各个残差元素的平方和
                  Eigen::Matrix<double, 2, 6> J;
                  J << -fx * inv_z,0,fx * pc[0] * inv_z2,fx * pc[0] * pc[1] * inv_z2,-fx - fx * pc[0] * pc[0] * inv_z2,fx * pc[1] * inv_z,
                            0,-fy * inv_z,fy * pc[1] * inv_z2,fy + fy * pc[1] * pc[1] * inv_z2, -fy * pc[0] * pc[1] * inv_z2,-fy * pc[0] * inv_z;
                  H += J.transpose() * J;
                  b += -J.transpose() * e;
          }

          Vector6d dx;
          
          // dx=H.llt().solve(b);
          // dx=H.bdcSvd().solve(b);
          dx = H.ldlt().solve(b);// Lower Diagonal Lower Transposition
          // 可以使用这个LDLT对象来求解线性方程组Hx=b,即LDL^Tx=b,
          // H是一个矩阵的转置乘以这个矩阵,所以结果一定是正定的,(正定矩阵一定是方阵)
          // 如果知道矩阵是对称正定的，那么使用 H.ldlt().solve(b) 可以更快地求解线性方程组。
          // 如果不确定矩阵的性质，或者矩阵不是对称正定的，则使用 H.solve(b) 更加通用
          if (isnan(dx[0])) {
            cout << "result is nan!" << endl;
            break;
          }

          if (iter > 0 && cost >= lastCost) {
            // cost increase, update is not good
            cout << "cost: " << cost << ", last cost: " << lastCost << endl;
            break;
          }

          // update your estimation
          pose = Sophus::SE3d::exp(dx) * pose;// 更新增量
          lastCost = cost;

          cout << "iteration " << iter << " cost=" << std::setprecision(12) << cost << endl;
          // cout << "dx.norm()=" <<dx.norm()<< std::setprecision(12) << endl;
          if (dx.norm() < 1e-6) {
            // converge
            // 如果增量足够小,代表方程收敛
            break;
          }
        }
        cout << "pose by g-n: \n" << pose.matrix() << endl;
}

/// vertex and edges used in g2o ba
//  自定义顶点
class VertexPose : public g2o::BaseVertex<6, Sophus::SE3d> {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

  virtual void setToOriginImpl() override {
    _estimate = Sophus::SE3d();
  }

  /// left multiplication on SE3
  virtual void oplusImpl(const double *update) override {
    Eigen::Matrix<double, 6, 1> update_eigen;
    update_eigen << update[0], update[1], update[2], update[3], update[4], update[5];
    _estimate = Sophus::SE3d::exp(update_eigen) * _estimate;//SE3d::exp()函数重载了运算符,将6维向量,变换为了SE3特殊欧氏群
  }

  virtual bool read(istream &in) override {}

  virtual bool write(ostream &out) const override {}
};
// 定义边
class EdgeProjection : public g2o::BaseUnaryEdge<2, Eigen::Vector2d, VertexPose> {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

  EdgeProjection(const Eigen::Vector3d &pos, const Eigen::Matrix3d &K) : _pos3d(pos), _K(K) {}

  virtual void computeError() override {
    const VertexPose *v = static_cast<VertexPose *> (_vertices[0]);
    Sophus::SE3d T = v->estimate();
    Eigen::Vector3d pos_pixel = _K * (T * _pos3d);
    pos_pixel /= pos_pixel[2];
    _error = _measurement - pos_pixel.head<2>();
  }
//linearizeOplus函数就是用来接应雅可比的,不用也可,只是比较慢10倍左右
  // virtual void linearizeOplus() override 
  // {
  //   const VertexPose *v = static_cast<VertexPose *> (_vertices[0]);
  //   Sophus::SE3d T = v->estimate();
  //   Eigen::Vector3d pos_cam = T * _pos3d;
  //   double fx = _K(0, 0);
  //   double fy = _K(1, 1);
  //   double cx = _K(0, 2);
  //   double cy = _K(1, 2);
  //   double X = pos_cam[0];
  //   double Y = pos_cam[1];
  //   double Z = pos_cam[2];
  //   double Z2 = Z * Z;
  //   _jacobianOplusXi
  //     << -fx / Z, 0, fx * X / Z2, fx * X * Y / Z2, -fx - fx * X * X / Z2, fx * Y / Z,
  //           0, -fy / Z, fy * Y / (Z * Z), fy + fy * Y * Y / Z2, -fy * X * Y / Z2, -fy * X / Z;
  // }

  virtual bool read(istream &in) override {}

  virtual bool write(ostream &out) const override {}

private:
  Eigen::Vector3d _pos3d;
  Eigen::Matrix3d _K;
};
// 用定义的顶点和边求解G2O问题的函数
void bundleAdjustmentG2O(const VecVector3d &points_3d,const VecVector2d &points_2d,const Mat &K,Sophus::SE3d &pose) 
  {
  // 构建图优化，先设定g2o
  typedef g2o::BlockSolver<g2o::BlockSolverTraits<6, 3>> BlockSolverType;  // pose is 6, landmark is 3
  typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType; // 线性求解器类型
  // 梯度下降方法，可以从GN, LM, DogLeg 中选
  auto solver = new g2o::OptimizationAlgorithmGaussNewton(
  g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));
  g2o::SparseOptimizer optimizer;     // 图模型
  optimizer.setAlgorithm(solver);       // 设置求解器
  optimizer.setVerbose(true);               // 打开调试输出

  // vertex,
  // 这里面的顶点只有相机位姿,没有地图点作为顶点
  VertexPose *vertex_pose = new VertexPose(); // camera vertex_pose
  vertex_pose->setId(0);
  vertex_pose->setEstimate(Sophus::SE3d());// 虽然Vector6d 给的输入是(0,0,0,0,0,0),但经过旋转之后分别是单位阵的旋转R和(0,0,0)的平移
  optimizer.addVertex(vertex_pose);
  // K
  Eigen::Matrix3d K_eigen;
  K_eigen <<
                          K.at<double>(0, 0), K.at<double>(0, 1), K.at<double>(0, 2),
                          K.at<double>(1, 0), K.at<double>(1, 1), K.at<double>(1, 2),
                          K.at<double>(2, 0), K.at<double>(2, 1), K.at<double>(2, 2);
  // edges
  int index = 1;
  for (size_t i = 0; i < points_2d.size(); ++i) {
    auto p2d = points_2d[i];
    auto p3d = points_3d[i];
    EdgeProjection *edge = new EdgeProjection(p3d, K_eigen);
    edge->setId(index);
    edge->setVertex(0, vertex_pose);
    edge->setMeasurement(p2d);// 图片上读取到的像素是测量值
    edge->setInformation(Eigen::Matrix2d::Identity());// 设置权重的地方
    optimizer.addEdge(edge);
    index++;
  }

  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  optimizer.setVerbose(true);
  optimizer.initializeOptimization();
  optimizer.optimize(10);
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "optimization costs time: " << time_used.count() << " seconds." << endl;
  cout << "pose estimated by g2o =\n" << vertex_pose->estimate().matrix() << endl;
  pose = vertex_pose->estimate();
}
