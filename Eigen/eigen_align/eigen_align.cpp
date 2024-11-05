#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>

int main()
{
    int m = 4;
    // int n = 3;
    int n = 4; //该这里
    Eigen::Tensor<float, 2, Eigen::RowMajor | Eigen::AutoAlign>  mat (m, n);
    
    // 创建一个2*1维，4x3的tensor
    mat.setValues({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12} });

    const float* base = &mat(0, 0);

    for (int r = 0; r < m; ++r) {
        std::cout
            << "mat(" << r << ", " << 0 << ") = " << mat(r, 0)
            << ", addr = " << &mat(r, 0)
            << ", addr % 16 = " << (reinterpret_cast<intptr_t>(&mat(r, 0)) % 16)
            << "\n";
    }
}

/*

运行程序到的输出:

mat(0, 0) = 1, addr = 0x5ba3bd7da2b0, addr % 16 = 0
mat(1, 0) = 4, addr = 0x5ba3bd7da2bc, addr % 16 = 12
mat(2, 0) = 7, addr = 0x5ba3bd7da2c8, addr % 16 = 8
mat(3, 0) = 10, addr = 0x5ba3bd7da2d4, addr % 16 = 4

我希望所有 addr % 16 结果都为0, 该怎么办到呢？

*/
