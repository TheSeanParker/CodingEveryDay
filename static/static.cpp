  
#include <iostream>


  class _demo
  {
  private:
    /* data */
    static int a;
  public:
    _demo(/* args */);
    ~_demo();
    void print()
    {
         std::cout<<"a++="<<a+10<<std::endl;
    }
  };
  
  _demo::_demo(/* args */)
  {
    std::cout<<"a="<<a<<std::endl;
  }
  
  _demo::~_demo()
  {
  }
    int _demo::a=4;
   int main(int argc, char const *argv[])
   {
    /* code */
    _demo A;
    A.print();
    return 0;
   }
   