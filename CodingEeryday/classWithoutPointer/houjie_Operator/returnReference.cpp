#include <iostream>
 int abc(int a,const int b)
 {
    return int(a+b);//typename() 构建一种临时对象
 }
int main(int argc, char const *argv[])
{
    /* code */
    std::cout<<"输出数据"<<abc(1,2)<<std::endl;
    return 0;
}
