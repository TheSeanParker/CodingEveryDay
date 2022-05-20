#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;
class ListStrategy
{
public:
  virtual ~ListStrategy() = default;                                   //基类析构函数必须为虚，否则有资源泄漏的风险,尤其是在多态时
                                                                       //基类加了析构函数，子类加不加都是可以的
  virtual void add_list_item(ostringstream& oss, const string& item)=0;//纯虚函数写法较为pop，纯虚函数一定要被重新定义
                                                                       //只有virtual func才可以overrride
                                                                       //一般虚函数已经有默认定义，函数重新定义均可                                                                  
  virtual void start(ostringstream& oss)=0;//一般虚函数，当下没有实现，后续有实现  
  virtual void end(ostringstream& oss)  =0;
};

class MarkdownListStrategy : public ListStrategy
{
public:
  void add_list_item(ostringstream& oss, const string& item) override
  {
    oss << " * " << item << endl;
  }

  void start(ostringstream& oss) override 
  {

  }
  void end(ostringstream& oss) override 
  {

  }
};

class HtmlListStrategy : public ListStrategy
{
public:
  void start(ostringstream& oss) override
  {
    oss << "<ul>" << endl;
  }

  void end(ostringstream& oss) override
  {
    oss << "</ul>" << endl;
  }

  void add_list_item(ostringstream& oss, const string& item) override
  {
    oss << "<li>" << item << "</li>" << endl;
  }
};

//扩展
class XMLListStrategy : public ListStrategy
{

};

class TextProcessor
{
public:
  TextProcessor(unique_ptr<ListStrategy> ls):list_strategy(std::move(ls))
  {
   
  }
  void clear()
  {
    oss.str("");
    oss.clear();
  }
  void append_list(const vector<string> items)
  {
    list_strategy->start(oss);
    for (auto& item : items)
      list_strategy->add_list_item(oss, item);//左侧调用是谁，要看后面调用的是谁
                                              //TextProcessor tp1(std::make_unique<MarkdownListStrategy>());
    list_strategy->end(oss);
  }


  string str() const { return oss.str(); }
private:
  ostringstream oss;
  //ListStrategy list_s;
  unique_ptr<ListStrategy> list_strategy;
};

int main()
{
  // markdown
  TextProcessor tp1(std::make_unique<MarkdownListStrategy>());
  tp1.append_list({"Software", "Design", "Pattern"});
  cout << tp1.str() << endl;


  TextProcessor tp2(std::make_unique<HtmlListStrategy>());
  tp2.append_list({"Software", "Design", "Pattern"});
  cout << tp2.str() << endl;

  getchar();
  return 0;
}