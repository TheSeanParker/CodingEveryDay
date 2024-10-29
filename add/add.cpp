#include <iostream>
int  addbyreference(int& a,int& b)
{
    return a=a+b;
}
int  addbyValue(int a,int b)
{
    return a=(a+b);
}
int main(int argc, char const *argv[])
{
    // test 1
    int sean=1;
    int park=2;
    addbyreference(sean,park);
    std::cout<<"addbyreference="<<sean<<std::endl;//3
    std::cout<<"sean="<<sean<<std::endl;//3
    // test 2
    int a=1,b=3;
    int c=addbyValue(a,b);
    std::cout<<"addbyValue="<<c<<std::endl;
    std::cout<<"a="<<a<<std::endl; //1
    // test 3
    int q=3;
    int & w=q;
    std::cout<<"w="<<w<<std::endl; 
    --w;
    std::cout<<"--w="<<w<<std::endl; 
    std::cout<<"q="<<q<<std::endl; 
    // test 4
    int p=5;
    int z=p;
    z--;
    std::cout<<"z--="<<z<<std::endl; 
    std::cout<<"p="<<p<<std::endl; 
    return 0;
}
