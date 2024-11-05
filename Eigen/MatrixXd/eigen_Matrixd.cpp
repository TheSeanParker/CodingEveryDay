#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
void printMatriXd(MatrixXd& test)
{
    std::cout<<"MatrixXd.rows()="<<test.rows() <<std::endl;
    std::cout<<"MatrixXd.cols()="<<test.cols() <<std::endl;
     for (size_t i = 0; i < test.rows(); i++)
     {
        for (size_t j = 0; j < test.cols(); j++)
        {
            std::cout<<test(i,j)<<std::endl;
        }
     }
}
int main()
{
MatrixXd m(2,1);//代表2*2的维度
m(0,0) = 3;
m(1,0) = -1;
printMatriXd(m);
    Eigen::Matrix3d matrix_3d;
    // matrix_3d.setOnes();
    matrix_3d = Eigen::Matrix3d::Ones();
    std::cout<<"matrix_3d Ones:\n"<<matrix_3d<<std::endl<<std::endl;
    Eigen::Matrix<double, 5, 1> matB0=Eigen::Matrix<double, 5, 1>::Ones();
    std::cout<<"matB0 Ones:\n"<<matB0<<std::endl<<std::endl;

}

