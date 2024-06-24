#include<string>
#include <iostream>
void SetLogDestination(const char* base_filename)
{
          std::cout<<"right"<<std::endl;
}
void SetLogDestination_string(std::string&  base_filename)
{
          std::cout<<"day"<<std::endl;
}
int main(int argc, char const *argv[])
{
          std::string a="test";
          const char b[]="set";
          // SetLogDestination(a);
          SetLogDestination(a.c_str());
          SetLogDestination_string(b);
          return 0;
}
