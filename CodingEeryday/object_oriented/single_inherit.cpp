#include <iostream>
//下面讲解的是单继承
class Base1
{
    int x;//实例数据成员
    int y;
public:
    void process( )//在整个函数中，只有一套这个。子类的指针可以传递给父类
                   //Base1* this默认指针，但是不能写到形参里
                   //子类继承父类，继承的是调用权
    {
        x++;
    }
    Base1()=default;
    Base1(int a)
    {}
    Base1(const Base1& b1)
    {}
};
class Sub1:public Base1
{
public:
    int data;
    Sub1()=default;
    Sub1(int a):Base1(a)
    {}
    Sub1(const Sub1& c):Base1(c)//可以将子类对象的引用当作父类对象的引用
                                //子类继承父类，继承的是调用权
    {}
    void process2()
    {
       //x++;//子类访问不了父类私有成员，并不代表其在内部是不存在的（内存里面是有的）
             //可见性和内存的存在性是两回事儿
       //Base1::x;//这种方式也是不可以申请private变量      
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
    std::cout<<"Base1 size="<<sizeof(Base1)<<std::endl;//打印出来想看看继承类之间的内存结构关系
                                                       //类中的函数不占有内存大小
    std::cout<<"Sub1  size="<<sizeof(Sub1)<<std::endl;
    Base1 b1;
    Sub1  s1;
            b1.process();//process(&b1)
            s1.process();//process(&s1)
            b1=s1;//子类赋值给父类，将会发生数据切片的效应
                  //常常是非常危险的错误
            //s1=b1;//父类赋值给子类就是一种错误的写法
    process1(s1);
    Sub1* ps1=new Sub1();
    //process2(&s1);
    process2(ps1);
    delete ps1;
    process3(s1);
    process3(*ps1);
    //综合上述3种方法，传value会导致切片效应，其他两种不会
    s1.process();//通过子类对象调用父类函数(常用的方法)
    
    return 0;
} 
