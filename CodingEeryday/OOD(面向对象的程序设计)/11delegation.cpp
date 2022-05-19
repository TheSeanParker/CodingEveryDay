#include <iostream>
#include "string.h"
//delegation 委托（有指针相连）（相对于composition是弱链接）
//composition by reference(涵盖pointer的概念)
//composition的生命周期是同步的，但是delegation左右的生命周期是不同步的
//设计模式之一：Handle/Body（又叫做pimpl）（又叫做编译防火墙）（pointer2implementation）
namespace name
{
    class StringRep
    {
      friend class String;
      StringRep(const char* s);
      ~StringRep();
      int count;
      char* rep;
    };
}
inline String::String(const char* cstr)
{
   if (cstr) {
      m_data = new char[strlen(cstr)+1];
      strcpy(m_data, cstr);
   }
   else {   
      m_data = new char[1];
      *m_data = '\0';
   }
}

inline String::~String()
{
   delete[] m_data;
}
inline String::String(const String& str)
{
   m_data = new char[ strlen(str.m_data) + 1 ];
   strcpy(m_data, str.m_data);
}
inline String& String::operator=(const String& str)
{
   if (this == &str)
      return *this;

   delete[] m_data;
   m_data = new char[ strlen(str.m_data) + 1 ];
   strcpy(m_data, str.m_data);
   return *this;
}

int main(int argc, char const *argv[])
{
    /* code */
    using namespace name;
    const char* a="s";
    String s1("world");
    std::cout<<"Output="<<s1.get_c_str()<<std::endl;
    return 0;
}
