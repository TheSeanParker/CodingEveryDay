
#include<iostream>
using namespace std;

class heap_leak
{
private:
          /* data */
          

public:
          heap_leak(/* args */);
          ~heap_leak();
          int * a;
};

heap_leak::heap_leak(/* args */)
{
          a=new int[100];
          cout<<"cut in the func()"<<endl;
}

heap_leak::~heap_leak()
{
}

int main(int argc, char const *argv[])
{
          /* code */
          heap_leak demo;
          return 0;
}
