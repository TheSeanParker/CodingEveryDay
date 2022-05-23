#include <iostream>
class copyassignment
{
private:
    int* p_;
    int a_;
public:
    copyassignment(int* p,int a)
                    :p_(p),a_(a)
    {
        std::cout<<"cstr  a_ value ="<<a_ <<std::endl;//2
        std::cout<<"cstr *p_ value ="<<*p_<<std::endl;//2
    }
    ~copyassignment();
    copyassignment(const copyassignment& c)
    {
         a_=c.a_;
        *p_=*c.p_;
        std::cout<<"copy cstr  a_ value ="<<a_ <<std::endl;
        std::cout<<"copy cstr *p_ value ="<<*p_<<std::endl;
    }
    copyassignment& operator=(const copyassignment& c)
    {
         a_= c.a_;
        *p_=*c.p_;
        std::cout<<"operator  a_ value ="<< a_<<std::endl;//
        std::cout<<"operator *p_ value ="<<*p_<<std::endl;
       return *this;
    }
};
copyassignment::~copyassignment()
{  
}

int main(int argc, char const *argv[])
{
    /* code */
    int x=2;
    int* p1=&x;
    
    copyassignment x1(p1,x);//2
    int y=3;
    int* p2=&y;
    copyassignment y1(p2,y);//3
    y1=x1;                  //2
    copyassignment z1(y1);
    return 0;
}
