
#include <iostream>
//我的这个设计，比书本P312要好，因为在运算符重载的时候，我没有在函数内部重新定义一个临时变量，
//而是用隐形传递的this指针，解决了这个问题，同时形参的数目也减少了一个
class Time
{
private:
    /* data */
    int hour;
    int minute;
public:
    Time(int a,int b)
    {
        hour=a;
        minute=b;
    };
    Time(){}
    ~Time(){};
    Time& sum(const Time& t)
    {
        if (t.minute+this->minute>=60)
        {
           this->minute=t.minute+this->minute-60;
           this->hour=(t.hour+this->hour+1)%24;
        }
        else
        {
           this->minute=t.minute+this->minute;
           this->hour=(t.hour+this->hour+1)%24;
        }
        return  *this;
    }
    int returnHours()
    {
        std::cout<<"return hour="<<hour<<std::endl;
        return hour;
    }
    int returnMinutes()
    {
        std::cout<<"return minute="<<minute<<"\n";
        return minute;
    }
};
int main(int argc, char const *argv[])
{
    Time a(9,56);
    Time b(19,54);
    Time c;
    c=a.sum(b);
    c.returnMinutes();
    c.returnHours();
}
