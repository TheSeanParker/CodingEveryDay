#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;
//template Method 21个设计方法之一
//很久以前就写好的 class CDocument
class CDocument
{
public:
virtual ~CDocument() = default; //基类析构函数必须为虚，否则有资源泄漏的风险,尤其是在多态时
                                //纯虚函数写法较为pop，纯虚函数一定要被重新定义
                                //只有virtual func才可以overrride
                                //一般虚函数已经有默认定义，函数重新定义均可  
    virtual void serialize()=0;//**这个地方非常重要**一开始没有写出来                                                                 
    virtual void OnfileOpen()
    {
        serialize();
        std::cout<<"virtual void OnfileOpen()"<<std::endl; 
    }

};
    class CMyDoc : public CDocument
    {
    public:  
      void serialize()//前面加 virtual还是不加都是可以的
      {
        std::cout<<"Output="<<std::endl;
      }
    };
int main()
{
  CMyDoc myDoc;
  myDoc.OnfileOpen();
  return 0;
}