#ifndef  __MYSTRING__
#define  __MYSTRING__
#include <cstring>
//class with pointer members 必须有copy ctor和copy op
class String
{
private:
    /* data */
    char* m_data;//32位电脑里面是4个byte，64位电脑是8个byte无论指向的对象是多大，都满足这个条件 
public:
    String(const char* cstr=nullptr);     //1,默认构造函数，参数值为0,只是在类里可以赋初值
    String(const String& str);            //2,拷贝构造，带指针的函数，一定会包含第2，3两个function()
    String& operator=(const String& str); //3,拷贝赋值
    ~String();
    char* get_c_str() const {return m_data+2;}
    //左侧加了const的成员函数可以被非const对象和const对象调用，但不加const的成员只能被非cost的对象调用
}; 
        inline String::String(const char* cstr)//在声明处可以声明默认参数，定义处不可以；左侧括号内加了=nullptr是不对的
        {                                      //传指针
            if (cstr)
            {
                m_data =new char[strlen(cstr)+1];
                strcpy(m_data,cstr);//传指针，接指针;传解引用的value，用引用接受
            }
            else
            {
                m_data=new char[1];
                *m_data='\0';
            }    
        }
        String::String(const String& str)//传引用
        {
            std::cout<<"go to String(const String& str)"<<"\n";
            m_data=new char[strlen(str.m_data)+1];
            strcpy(m_data,str.m_data);
        }
        //拷贝赋值函数
        String& String::operator=(const String& str)//第一个&为reference，第二个也是
        {
            //this等于&调用者地址
           if (this==&str)//if检测是否为自我赋值，必须要有的代码//这个&为取地址符号
              return *this;
            delete[] this->m_data;
            //如果在C语言中等价于this->m_data,C++这样去写有些累赘，因为构造函数就是在处理类对象的各种赋值，等操作。也具备访问成员的权限
            m_data=new char[strlen(str.m_data)+1];
            strcpy(m_data,str.m_data);
            return *this;
        }
        inline String::~String()
        {
            delete[] m_data; //为什么删除的m_data是一个数组呢？
                             //答：m_data=new char[strlen(str.m_data)+1];生成的是数组
            std::cout<<"go to String::~String()"<<"\n";
        }
#endif