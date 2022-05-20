#include <iostream>
//基类析构函数必须为虚，否则有资料泄漏的风险
class Base1
{
    int x;//实例数据成员
    int y;
public:
    void process( )//在整个函数中，只有一套这个。子类的指针可以传递给父类
                   //Base1* this默认指针，但是不能写到形参里
    {
        x++;
    }
    Base1()=default;
    Base1(int a)
    {}
    Base1(const Base1& b1)
    {}
    // virtual ~Base1()
    // {
    //     std::cout<<"virtual ~Base1()"<<std::endl;
    // }
};
class Sub1:public Base1
{
public:
    int data;
    Sub1()=default;
    Sub1(int a):Base1(a)
    {}
    Sub1(const Sub1& c):Base1(c)//可以将子类对象的引用当作父类对象的引用
    {}
    void process2()
    { 
    }
    virtual ~Sub1()
    {
         std::cout<<"virtual ~Sub1()"<<std::endl;
    }
};
void process1(Base1 b)
{

}
void process2(Base1* b)
{
    
}
void process3(Base1& b)
{
    
}
int main(int argc, char const *argv[])
{
    /* code */
    // std::cout<<"Base1 size="<<sizeof(Base1)<<std::endl;//打印出来想看看继承类之间的内存结构关系
    //                                                    //类中的函数不占有内存大小
    // std::cout<<"Sub1  size="<<sizeof(Sub1)<<std::endl;
    // Base1 b1;
    // Sub1  s1;
    //         b1.process();//process(&b1)
    //         s1.process();//process(&s1)
    //         b1=s1;//子类赋值给父类，将会发生数据切片的效应
    //               //常常是非常危险的错误
    Base1* ps1=new Sub1();
    process2(ps1); 
    delete ps1;

    return 0;
} 
