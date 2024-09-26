#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {
  double ar = 1.0, br = 2.0, cr = 1.0;         // 真实参数值
  double ae = 2.0, be = -1.0, ce = 5.0;        // 估计参数值
  int N = 100;                                 // 数据点
  double w_sigma = 1.0;                        // 噪声Sigma值
  double inv_sigma = 1.0 / w_sigma;
  cv::RNG rng;                                 // OpenCV随机数产生器

  vector<double> x_data, y_data;      // 测量的数据
  for (int i = 0; i < N; i++) {
      double x = i / 100.0;
      x_data.push_back(x);
      y_data.push_back(exp(ar * x * x + br * x + cr) + rng.gaussian(w_sigma * w_sigma));
  }

  // 开始Gauss-Newton迭代
  int iterations = 100;    // 迭代次数
  double cost = 0, lastCost = 0;  // 本次迭代的cost和上一次迭代的cost

  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  for (int iter = 0; iter < iterations; iter++) {

    Matrix3d H = Matrix3d::Zero();             // Hessian = J^T W^{-1} J in Gauss-Newton,为什么这里有一个W?
    Vector3d b = Vector3d::Zero();             // bias,每次迭代完毕以后将偏差也清空
    cost = 0;                                                         // 每次迭代计算完毕之后将残差清空

          for (int i = 0; i < N; i++) {
            Vector3d J;
            J[0]=-x_data[i]*x_data[i]*exp(ae*x_data[i]*x_data[i]+be*x_data[i]+ce);
            J[1]=                   - x_data[i]*exp(ae*x_data[i]*x_data[i]+be*x_data[i]+ce);
            J[2]=                                       - exp(ae*x_data[i]*x_data[i]+be*x_data[i]+ce);
            H=J.transpose()*inv_sigma*J;
            double err=y_data[i]-exp(ae*x_data[i]*x_data[i]+be*x_data[i]+ce);
            b=-J*inv_sigma*err;
            cost=err*err;
          }
          // cout<<"输出测试H="<<H<<endl;
          // 求解线性方程 Hx=b
          Vector3d dx = H.ldlt().solve(b);
          if (isnan(dx[0])) {
            cout << "result is nan!" << endl;
            break;
          }

          if (iter > 0 && cost >= lastCost) {
            cout << "cost: " << cost << ">= last cost: " << lastCost << ", break." << endl;
            // 当残差cost在当下迭代之后的值,比上一次的残差值增大的话,那么将会导致拟合的效果不理想,退回到上一次的拟合参数,即为所得
            break;// 所以可能不达到迭代的次数就退出了,iter < iterations
          }

          ae += dx[0];
          be += dx[1];
          ce += dx[2];

          lastCost = cost;

          cout << "total cost: " << cost << ", \t\tupdate: " << dx.transpose() <<
              "\t\testimated params: " << ae << "," << be << "," << ce << endl;
  }

  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "solve time cost = " << time_used.count() << " seconds. " << endl;
  cout << "estimated abc = " << ae << ", " << be << ", " << ce << endl;
  return 0;
}
