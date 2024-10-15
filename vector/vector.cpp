#include <vector>
#include<iostream>
int main(int argc, char const *argv[])
{
          /* code */
          int a,b;
          a=1;
          b=2;
          std::vector<int> test;
          test.push_back(a);
          test.push_back(b);
          std::cout<<test[0]<<std::endl;
          return 0;
}
