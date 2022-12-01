#include <iostream>
using namespace std;
//一个错误，编译可以通过，但是需要寻找一下
class point
{
public:
    int x;
    int y;
    static int data;//静态变量会被翻译成全局成员
    static void process()
    {
        data++;
    }
} ;
//int point::data=100;
int main(int argc, char const *argv[])
{
    /* code */
    point xy{10,20};
    cout<<"输出数据的x数值="<<xy.x<<endl;
    cout<<"输出数据的y数值="<<xy.y<<endl;
    point* p1=new point{11,21};
    cout<<"x数值等于="<<(*p1).x<<endl;
    cout<<"y数值等于="<<(*p1).y<<endl;
    xy.process();
    cout<<"输出数据的data数值="<<xy.data<<endl;
    return 0;
}
