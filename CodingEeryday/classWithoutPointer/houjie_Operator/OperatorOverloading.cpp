#include <iostream>
#include "operatorOverloading.h"

int main(int argc, char const *argv[])
{
    /* code */
    complex c1(200,300);
    complex c2(200,300);
    int x{6};
    std::cout<<"Output="<<c2.real()<<std::endl;
    std::cout<<"Output="<<c2.imag()<<std::endl;
    std::cout<<"判等="<<(c1==x)<<std::endl;
    return 0;
}
