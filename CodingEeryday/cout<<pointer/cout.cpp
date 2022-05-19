#include <iostream>
class qw1
{
private:
    /* data */
public:
    qw1(/* args */);

    void abc(int a=1)
    {
        a+=10;
    }
    ~qw1();
};

qw1::qw1(/* args */)
{
}

qw1::~qw1()
{
}

int main(int argc, char const *argv[])
{
    /* code */
    char* a="abccdadscasd";
    qw1 b;
    b.abc(3);
 
    std::cout<<a<<";"<<*a;
    return 0;
}
