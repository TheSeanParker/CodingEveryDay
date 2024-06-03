#include<iostream>


int main(int argc, char const *argv[])
{
         struct str
          {
               int a;
               bool b;
          };
          int* test;
          str* ptr;
          ptr=nullptr;
          int C=9;
          str demo;
          ptr=&demo;
          // 必须要有上面的步骤,是因为,否则这个ptr指针还不清楚这个结构体到底是什么形式的!
          // 所以无法对它内部的元素进行赋值或其他操作
          ptr->a=C*2;
          test=&C;
          std::cout<<"*test="<<*test<<std::endl;
          *test=2*C;
          std::cout<<"*test"<<*test<<std::endl;

          if (nullptr){std::cout<<"nullptr!=0"; }
          else{std::cout<<"nullptr=0"<<ptr;}

          return 0;
}
