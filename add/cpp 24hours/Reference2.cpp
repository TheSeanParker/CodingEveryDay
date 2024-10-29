#include <iostream>
  
int main()
{
    int  intOne;
    int &rSomeRef = intOne;
  
    intOne = 5;
    std::cout << "intOne: " << intOne << "\n";//5
    std::cout << "rSomeRef: " << rSomeRef << "\n";//5
  
    std::cout << "&intOne: \t"  << &intOne << "\n";//取地址
    std::cout << "&rSomeRef:\t " << &rSomeRef << "\n";//取地址 且同上一个地址,引用的本质就是别名
  
    return 0;
}
