#include <iostream>
class staticDemo{
private:
    staticDemo(){}
    static staticDemo* p;
    int a;  
    static  int b;
public:
    static staticDemo* instance();
    void getmember()
    {
        b++;
        std::cout<<"b="<<b<<std::endl;
    }
};
int staticDemo::b=2;

staticDemo* staticDemo::p = new staticDemo();
staticDemo* staticDemo::instance()
{
    return p;
}

//main.c
int main(void)
{
    staticDemo * s = staticDemo::instance();
    s->getmember();

    return 0;
}