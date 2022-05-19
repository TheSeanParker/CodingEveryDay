#include <iostream>
#include <string>
#include "string.h"
//拷贝构造和普通构造函数的本质区别在参数是类类型，而不是其他类型
int main(int argc, char const *argv[])
{
    /* code */
    String s1("world");       
    String s2("hello");  
    //s1(s2);//左侧是不具备自我赋值的功能，所以要进行运算符重载  
    s1=s2;  
    std::cout<<"Output="<<s1.get_c_str()<<std::endl;
    //打印对象是不对的，但是可以打印出对象里的元素
    
    String* p=new String("hello");
      delete p;
    return 0;
}
