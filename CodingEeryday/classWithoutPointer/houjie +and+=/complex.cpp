#include <iostream>
#include "complex.h"
int main(int argc, char const *argv[])
{
    /* code */
    complex a(1,2);
    complex b(3,4);
    complex* p=new complex(4);
    std::cout<<"Output *p="<<(*p).imag()<<std::endl;
    //新加的这块，证明可用。动态方式创建对象的方式是可用的
    a+=b;
    complex c=a+b;
    std::cout<<"Output"<<a.real()<<std::endl;
    complex c1(2,1);
    std::cout<<c1<<"\n"<<conj(c1)<<"\n";//当<<左侧为complex类的类型时候，才可以调用重载运算符<<
    return 0;
}
