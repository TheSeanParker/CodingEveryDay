

#include <iostream>
using namespace std;
int main() 
{
    int *p=new int; 
    *p=3;
    cout<<"创建新空间后，指针p中保存的地址："<<p<<endl;
    cout<<"将3赋给p的地址后，指针p读取的值："<<*p<<endl;//3
    delete p;
    cout<<"删除空间后，指针p读取的值："<<*p<<endl;
    long *p1=new long;
    *p1=100;
    cout<<"创建新空间后，指针p中保存的地址："<<p<<endl;
    cout<<"指向新空间的指针p1保存的地址："<<p1<<endl;
    *p=23;
    cout<<"将23赋给p的地址后，指针p读取的值："<<*p<<endl;//23
    cout<<"将23赋给p的地址后，指针p1读取的值："<<*p1<<endl;
    delete p1;
    return 0;
}