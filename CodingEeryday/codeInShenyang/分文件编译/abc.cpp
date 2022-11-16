//方法1：
#include"a.h"
    // namespace pan
    // {
    // void zhangpan(int a)
    // {
    //     std::cout<<"显示的技术指标数值"<<a<<std::endl;
    // }   
    // } // namespace pan
//方法2：

 void pan::zhangpan(int a)
{
    std::cout<<"显示的技术指标数值"<<a<<std::endl;
}