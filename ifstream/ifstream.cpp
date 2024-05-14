
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
           std::ifstream kf_map("./Arrows.txt");
          
           if(kf_map)
           {
                std::string a;
                while(kf_map)
                {
                              kf_map >> a;
                              cout<<"output="<<a<<endl;
               }
           }
           else{
                   std::cout<<"error"<<std::endl;
                }
          return 0;
}
