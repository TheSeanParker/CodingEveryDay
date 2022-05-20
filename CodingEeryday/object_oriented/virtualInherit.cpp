#include <iostream>
class Base1
{
    double d1;
    double dx;
    double dy;
    double dz;
};
class Sub1:public virtual Base1//virtual关键字和虚函数只是名称相同而已
                               //优化{菱形}继承
{
    double d2;
};
class Sub2: public virtual Base1
{
   double d3;
};
class Sub3 :public Sub1,public Sub2
{
  double d4;
};
int main(int argc, char const *argv[])
{
    //Base1 b1;
    std::cout<<"Base1 ="<<sizeof(Base1)<<std::endl;//32  
    //Sub1 s1;
    std::cout<<"Sub1 ="<<sizeof(Sub1)<<std::endl; //40   
    //Sub2 s2;
    std::cout<<"Sub2 ="<<sizeof(Sub2)<<std::endl; //40
    //Sub3 s3;
    std::cout<<"Sub3 ="<<sizeof(Sub3)<<std::endl; //80
    return 0;
}
