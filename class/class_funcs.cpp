
#include <iostream>
using namespace std;
class class_funcs
{
private:
          int a;
public:
          class_funcs(/* args */);
          ~class_funcs();
          void funcA()
          {
                    funcB();
            std::cout<<"cut in funcsA()"<<std::endl;
          }
          void funcB()
          {
            std::cout<<"cut in funcsB()"<<std::endl;
          }
};

class_funcs::class_funcs(/* args */)
{
}

class_funcs::~class_funcs()
{
}
void funcC()
{
          funcD();
    cout<<"cut in funcC()"<<endl;
}
void funcD()
{
    cout<<"cut in funcD()"<<endl;
}
int main(int argc, char const *argv[])
{
          /* code */
          class_funcs A;
          // A.funcA();
          // class类中,成员函数不分先后可以相互调用
          // 但是普通函数之间就不能随意的相互进行调用
          funcC();
          return 0;
}
