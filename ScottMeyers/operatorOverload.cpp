
#include <iostream>
class operatorOverload
{
private:
    /* data */
    int x;
    int y;
public:
    operatorOverload()=default;
    operatorOverload(int a,int b)
    {
      x=a;
      y=b;
    }
    ~operatorOverload();
    operatorOverload& operator *(const operatorOverload& c)//成员函数版本的重载，只需要一个形参即可
    {
        this->x=this->x*c.x;
        this->y=this->y*c.y;
        return *this;
    }
     int returnValue()
    {
        return y;
    }
};
operatorOverload::~operatorOverload()
{

}
int main(int argc, char const *argv[])
{
    /* code */
    operatorOverload w1(1,2);
    operatorOverload w2(3,4);
    operatorOverload w3(5,6);
    operatorOverload w4;
    w4=w1*w2*w3;
    int d=w4.returnValue();
    std::cout<<"输出数值w4的y值="<<d<<std::endl;
    return 0;
}

