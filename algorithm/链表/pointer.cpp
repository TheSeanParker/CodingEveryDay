#include <iostream>

int main(int argc, char const *argv[])
{
    int a=100;
    int* p=&a;
    std::cout<<"输出*p="<<*p<<std::endl;
    std::cout<<"输出p="<<p<<std::endl;
    int** p1=&p;
    std::cout<<"输出*p="<<*p1<<std::endl;
    return 0;
}
