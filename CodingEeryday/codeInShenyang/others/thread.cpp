#include <iostream>
#include <thread>
using namespace std;
void myprint()
{
    std::cout<<"输出今天0"<<endl;
    std::cout<<"输出今天1"<<endl;
    std::cout<<"输出今天2"<<endl;
    std::cout<<"输出今天3"<<endl;
    std::cout<<"输出今天4"<<endl;
    std::cout<<"输出今天5"<<endl;
    std::cout<<"输出今天6"<<endl;
    std::cout<<"输出今天7"<<endl;
    std::cout<<"输出今天8"<<endl;
}
int main(int argc, char const *argv[])
{
    cout<<"输出昨天"<<endl;
    std::thread mytobj(myprint);
    mytobj.detach();
    cout<<"输出hou天1"<<endl;
    cout<<"输出hou天2"<<endl;
    cout<<"输出hou天3"<<endl;
    cout<<"输出hou天4"<<endl;
    cout<<"输出hou天5"<<endl;
    cout<<"输出hou天6"<<endl;
    cout<<"输出hou天7"<<endl;
    cout<<"输出hou天8"<<endl;
    return 0;
}
