#include <iostream>
//...是一种操作符
//参数数量不定的模板
void printX()
{
  std::cout<<"__________"<<std::endl;
}
template <typename T,typename... Types>
void printX(const T& firstArg,const Types&...args)
{
  std::cout<<firstArg<<std::endl;//print first argument
  printX(args...);                //call print() for remaining arguments
}
int main(int argc, char const *argv[])
{
    /* code */
    printX(7.5,"hello",2,42);
    return 0;
}
