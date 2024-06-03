#include<iostream>


int main(int argc, char const *argv[])
{
         struct str
          {
               int a;
               bool b;
          };
          str* ptr;
      //     ptr=nullptr;
          int C=9;
          str demo;
          ptr=&demo;
          // 必须要有上面的步骤,是因为,否则这个ptr指针还不清楚这个结构体到底是什么形式的!
          // 所以无法对它内部的元素进行赋值或其他操作
          ptr->a=C*2;
        //   ptr->a=&b;//一定是这样是对的,而不是*ptr=b;这样的写法是错误的!
          std::cout<<"ptr->a="<<ptr->a<<std::endl;
          if (ptr==nullptr)
          {
                std::cout<<"NULLPTR";
          }
          else
          {
                std::cout<<"ptr="<<ptr;
          }
          
          return 0;
}
