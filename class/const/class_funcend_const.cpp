#include <iostream>
using namespace std;
class Test
{
    int num;
public:
    Test()
    {
        num=10;
    }
    void print1()
    {
        cout<<num<<endl;
    }
    void print2() const
    {
        cout<<num<<endl;
    }
    void print3() const
    {
        num-=10;//ERROR 1.const函数内部不能修改成员变量
        cout<<num<<endl;
    }
};

int main()
{
    Test a;
    a.print1();
    a.print2();
    a.print3();

    const Test b;
    b.print1();//ERROR 2.const对象不能访问非const函数
    b.print2();
    b.print3();
    return 0;
}