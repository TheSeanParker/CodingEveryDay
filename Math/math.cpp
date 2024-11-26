#include <math.h>
#include <iostream>
using namespace std;
void print (double a)
{
  std::cout<<"a= "<<a<<std::endl;
}
int main(int argc, char const *argv[])
{
    /* code */
    int a=4;
    double aa=std::exp(4);
    print(aa);
    double b= 3.993201;
    double bb=std::exp(b);
    print(bb);
    double c= bb-aa;
    print(c);
    return 0;
}
