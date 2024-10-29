#include <iostream>
using namespace std;
void swap(int x,int y)		//传值
{
    int temp;
    temp=x;
    x=y;
    y=temp;
}

int main()
{
int x=10, y=20;
swap(x, y);		
//    把实在参数 x 和 y 的值传给了 swap 中形式参数 x 和 y
//（注意，实参 x、y 与形参x、y 是不同的变量，都有各自不同的存储单元）
cout << "x:"<< x << "y:" << y << endl;
return 0;
}

