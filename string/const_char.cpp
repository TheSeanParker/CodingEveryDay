#include<string>
#include <iostream>
void SetLogDestination(const char* base_filename)
{
          std::cout<<"right"<<std::endl;
}
int main(int argc, char const *argv[])
{
          std::string a="test";
          // SetLogDestination(a);
          SetLogDestination(a.c_str());
          return 0;
}
