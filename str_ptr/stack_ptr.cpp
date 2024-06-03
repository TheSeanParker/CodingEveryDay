
#include <iostream>
int main(int argc, char const *argv[])
{
          /* code */
          int b=2;
          int*a=&b;
          std::cout<<"*a+1="<<*a+1<<std::endl;
          delete a;//栈指针不允许被删除,所以报错!
          return 0;
}
