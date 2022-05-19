#include <iostream>
#include "complex.h"
#include <cstring>
int main(int argc, char const *argv[])
{
    /* code */
    complex c1(1,2);
    complex *p=new complex(3); 
    int x='a';
    int* ab=&x;
    int c;
    std::cout<<"Output="<<sizeof(ab)<<"\n";
    std::cout<<"Output c byte number="<<sizeof(c)<<"\n";
    const char* cstr="hello";

    std::cout<<"Output cstr="<<*cstr<<";他的长度="<<strlen(cstr)<<"\n";
    return 0;
}
