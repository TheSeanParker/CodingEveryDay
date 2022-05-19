#include <iostream>
class empty_base
{
private:
    /* data */
public:
    empty_base(/* args */);
    ~empty_base();
};

empty_base::empty_base(/* args */)
{
   std::cout<<"empty_base() cstr"<<std::endl;
}

empty_base::~empty_base()
{
   std::cout<<"empty_base() dstr"<<std::endl;
}
        class Base
        { 
            int a;
        public:
            void process()
            {
            std::cout<<"class Base"<<std::endl;
            }
            int b;
        };
class Sub1
{
    Base b;//组合
    
    public:
    void func()
    {
        std::cout<<"class Sub1"<<std::endl;
        b.process();
    }
    int da;
};
        class Sub2: private empty_base
        {
        double data;
        public:
            Sub2();//针对于
            void func()
            {
                std::cout<<"void func()"<<std::endl;
                //process();
            }
            ~Sub2();
        };
            Sub2::Sub2()//子类函数在构造之前会执行父类的默认构造函数,会在后面加上代码
                        //Sub2::Sub2() : empty_base(){...};
                        //子类是外部,父类是内部,内部的定义方式
            {
                std::cout<<"Sub2() cstr"<<std::endl;
            }
            Sub2::~Sub2()//析构时候正好相反,就像砌墙,先基础,后发展
                         //Sub2::~Sub2(){...~empty_base()};
            {
                std::cout<<"Sub2() dstr"<<std::endl;
            }
int main(int argc, char const *argv[])
{
    /* code */
    Sub2 s2;
    std::cout<<"sizeof(empty_base)="<<sizeof(empty_base)<<std::endl;
    std::cout<<"sizeof(Base)="<<sizeof(Base)<<std::endl;
    std::cout<<"sizeof(Sub1)="<<sizeof(Sub1)<<std::endl;
    std::cout<<"sizeof(Sub2)="<<sizeof(Sub2)<<std::endl;
    return 0;
}
