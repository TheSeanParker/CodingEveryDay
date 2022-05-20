#include <iostream>
//下面验证子类和父类之间调用cst和dstr的先后顺序
class Base1
{
    int x;//实例数据成员
    int y;
public:
    virtual void process( )//在整个函数中，只有一套这个。子类的指针可以传递给父类
                           //Base1* this默认指针，但是不能写到形参里
                           //member function declared with 'override' does not override a base class member
                           //成员函数为virtual才能override
    {
        x++;
        std::cout<<"void virtual Base1 process() override "<<std::endl;
    }
    Base1()
    {
        std::cout<<"Base1()"<<std::endl;
    }
    ~Base1()
    {
        std::cout<<"～Base1()"<<std::endl;
    }
    Base1(int a) 
    {}
    Base1(const Base1& b1)
    {
         std::cout<<"Base1(const Base1& b1)"<<std::endl;
    }
};
class Sub1:public Base1
{
public:
    int data;
    Sub1()
    {
        std::cout<<"Sub1()"<<std::endl;
    }
    virtual ~Sub1()
    {
        std::cout<<"~Sub1()"<<std::endl;
    }
    Sub1(int a):Base1(a)
    {}
    Sub1(const Sub1& c):Base1(c)//可以将子类对象的引用当作父类对象的引用
    {}
    //override 虽然去掉不影响功能，但是在实操时，需要进行的是将显示表达这个是继承函数不是新建立的函数
    void process() override  
    {
       std::cout<<"void Sub1 process() override "<<std::endl;
    }
};
class Base2
{
  int u;
  int v;
};
class Sub2:public Base1,public Base2//一般子类继承父类都是使用public继承，少数使用private
{
  int data;
};
void process1(Base1 b)
{
   b.process();//非多态调用--编译时绑定
               //拿这个【对象切片】后的函数调用，已经没有意义了
}
void process2(Base1* b)
{
    b->process();//调用的是子类的虚函数，为啥？
                 //多态调用   
}
void process3(Base1& b)
{
    b.process();//多态调用
}
int main(int argc, char const *argv[])
{
    Sub1* p1=new Sub1();//子类构造函数前需要调用父类构造函数
    p1->process();
    Base1* p2=new Base1();
    p2->process();
    delete p1;
    delete p2;
    return 0;
} 
