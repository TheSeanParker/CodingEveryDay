#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char const *argv[])
{
          std::vector<int> d,e;
          std::cout<<"1_d_capacity="<<d.capacity()<<std::endl;//0
          d.reserve(10);
          std::cout<<"2_d_capacity="<<d.capacity()<<endl;//10
          std::cout<<"size="<<d.size()<<endl;//0
          int a,b,c;

          d.reserve(10);
          d={a,b,c};
          std::cout<<"2size="<<d.size()<<endl;//3
          std::cout<<"3_d_capacity="<<d.capacity()<<endl;//10
          return 0;          
}
