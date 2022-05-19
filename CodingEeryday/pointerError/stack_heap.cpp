#include <iostream>
class Point{
    public:
      int x{0};
      int y{1};
};
void func()
{
    int x{10};
    int y{20};
    int& data=x;//data是x的别名
    x=x+y;
    int* px=new int{10};
    int* parray=new int[10];
    delete[] parray;

} 
void process1(const Point& p)
{ 
  //因为const 内部的变化不会传递到外部，
  std::cout<<"it is a const Point&"<<std::endl;
}
void process2(Point p)
{
  
}
void process3(Point* p)
{
  //即使在这段代码中，别人给你传递指针，也不应该进行处理
  //以裸指针形式传递的对象，假定由调方所有，其生命周期也由调方负责
  //传递多态对象偶尔会用， 
  std::cout<<"it is a Point*"<<std::endl;
}
int main(int argc, char const *argv[])
{
    //func();
    Point* p=new Point{10,20};
    process3(p);
    delete p;
 
        Point p2;    //int p2;
        process1(p2);//int &p=p2;
    return 0;
}
