#include <cinttypes>
#include <iostream>
#include <functional>
#include <variant>
using namespace std;
#define PRINTFUN_ADDR std::cout << static_cast<const char *>(__PRETTY_FUNCTION__) << " at " << this << std::endl
 //A.hpp
class A{
    int m_a = 1;
    int m_b = 2;
    int m_c = 3;
    uint8_t m_d = 4; 
public:
    A(int a,int b,int c,uint8_t d);
    A(const A& other);
    A();
    ~A();
    void Dump();
};
//A.cpp
A::A()
{
    
}
void A::Dump()
{
     auto dumpItem = [this](auto name, auto& item){
        std::cout << name << "@" << (void*)&item << ", value is " << item <<  ", size is " << sizeof(item) << endl;
     };
     dumpItem("m_a", m_a);
     dumpItem("m_b", m_b);
     dumpItem("m_c", m_c);
     dumpItem("m_d", m_d);
     cout << "Obj address:" << sizeof(*this) << endl;
     
}
int main()
{
    A a;
    a.Dump();
    int aa=3;
    uint8_t b=3;
    cout<<"int size="<<sizeof(aa)<<endl;
    cout<<"uint8 size="<<sizeof(b)<<endl;
    ;
}