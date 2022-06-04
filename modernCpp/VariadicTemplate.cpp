#include <iostream>
#include <bitset>
//...是一种操作符,代表的是pack（包），有此操作符才是variadic的类型
//参数数量不定的模板
//template使得C++更具有弹性
void printX()//处理边界条件
{
  std::cout<<"__________"<<std::endl;
}
template <typename T,typename... Types>
void printX(const T& firstArg,const Types&...args)
{
  std::cout<<firstArg<<std::endl; //print first argument
  std::cout<<"the number of args="<<sizeof...(args)<<std::endl;  
  printX(args...);                //call printX() for remaining arguments
                                  //本质是一种recursive递归调用
}

template <typename... Types>
void printX(const Types&...args)
{
  std::cout<<"2 the number of args=="<<sizeof...(args)<<std::endl;  
  printX(args...);                //call printX() for remaining arguments
                                  //本质是一种recursive递归调用
}
        void compare(int)
        {
          std::cout<<"int"<<std::endl;
        }
        void compare(double)
        {
          std::cout<<"double"<<std::endl;
        }
int main(int argc, char const *argv[])
{
    /* code */
    printX(7.5,"hello",std::bitset<16>(377),42);
    //在Varadic Template 里面可以允许上下两种模板类型的存在，在main函数中调用哪一个，完全取决于泛化和特化，
    //函数更倾向于调用特化的模板函数，于是第一个模板函数被调用
    double x=7;
        compare(x);
    return 0;
}
