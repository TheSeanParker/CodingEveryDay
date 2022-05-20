#include <iostream>
//下面验证为什么基类的析构函数必须为虚函数，否则有资源泄漏的风险
//比较是进步的方式之一
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
    virtual ~Base1()
    {
        std::cout<<"~Base1()"<<std::endl;
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
    ~Sub1() override
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
//下面写多态
    void process1(Base1* p)
    {
        p->process();
    }
    void process2(Base1& p)
    {
        p.process();
    }
    void process3(Base1 p)
    {
        p.process();
    }
        class testpointer2class
        {
            int a;
        public:
            void callabc()
            {
                std::cout<<"cut in abc()"<<std::endl;
            }
        };
        void process5(testpointer2class* p)
        {
            p->callabc();
        }
int main(int argc, char const *argv[])
{
    testpointer2class* pp=new testpointer2class();
    process5(pp);
    pp->callabc();
                   //以上测试了类就是一种特殊的类型罢了，可以简单等价于int
    Base1* p=new Sub1();
    (*p).process();//证明生成的对象是子类还是父类
    process1(p);
    delete p;//这时候就是问题所在，delete之后基类没有析构，在父类加上vitrtual以后就可以了
    return 0;
} 
//Base1()
//Sub1()
//void Sub1 process() override
//~Sub()
//~Base1()