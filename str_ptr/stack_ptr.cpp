
#include <iostream>
int main(int argc, char const *argv[])
{
          /* code */
          int b=2;
          int*a=&b;
          std::cout<<"*a+1="<<*a+1<<std::endl;
          int* ptr=new int;
          // ptr=nullptr; //不允许对空指针进行解引用
          int c=30;
          *ptr=c;
          // delete a;//栈指针不允许被删除,所以报错!
          std::cout<<"*ptr="<<*ptr<<std::endl;
          return 0;
}
