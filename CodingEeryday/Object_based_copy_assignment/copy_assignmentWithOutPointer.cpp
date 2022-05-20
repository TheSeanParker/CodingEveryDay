#include <iostream>
#include <cstddef>
//4大函数中的构造函数和拷贝构造函数的讲解
  //例子1 MyClass类不起实际作用
        class MuClass
        {

        };
        //上面的一个空类相当于下面的类展开的关系
        class MyClass
        {
            int z,h;
        public:
            MyClass()=default;
            ~MyClass()=default;//不想要就是用delete禁止生成，但是都要【显示】表达出来
                               //C++比较坑的地方就是愿意隐式生成
            MyClass(const MyClass& C)//拷贝构造函数
            {

            }
            MyClass& operator =(const MyClass& C)
            {
                return *this;
            }
        };
    // 例子2
    //上下两个例子就是在表达类没有必要自己写
class Point
{
public:
       int x;
       int y;
public: 
        Point(const Point& c)//默认生成的拷贝构造
                     :x(c.x),//成员初始化列表只能用于构造器
                      y(c.y)
        {
        }
        //构造函数的返回类型是这个类类型，因为构造函数的目的就是为了创建类类型的对象
        Point(int a,int b)
                    :x(a),
                     y(b)
        {
        }
        Point& operator=(const Point& c)//这个例子老师把Point写成了MyClass致错
        {
            this->x=c.x;
            this->y=c.y;
            return *this;
        }

};
//例子3 表达此类含有他类类型变量，都是足够好用的
      //编译器赋值操作符也是一个拷贝
    class Rectangledemo
    {
        Point m_leftUp;
        int    m_length;
        int    m_width;
        Rectangledemo(int x,int y,int length,int width)
                                :m_leftUp( Point{x,y}),//new出来的是一个指针,之所以一开始报错，是因为找不到含两个构造函数的函数
                                                       //构造函数生成对应的对象后返回这个类型的对象，然后再去调用构造函数进行赋值给m_leftup
                                 m_length(length),
                                 m_width(width) 
                                 { }
    };
//例子4，类中包含指针类型；就会比较难了
class Rectangle
{
    Point *m_leftUp;//类生成的指针默认是堆指针
                    //当成员有指针的时候，一定要定义destr ctr copy_assign
    int    m_length;
    int    m_width;
 public:

 int getfunction();//函数声明
    ~Rectangle()
    {
      delete m_leftUp;//当有指针成员时候，一定要定义
    }
    Rectangle(int x,int y,int length,int width)
                        :m_leftUp( new Point{x,y}),//new出来的是一个指针,之所以一开始报错，是因为找不到含两个构造函数的函数
                                            //构造函数生成对应的对象后返回这个类型的对象，然后再去调用构造函数进行赋值给m_leftup
                         m_length(length),
                         m_width(width) 
                         { }
    Rectangle(const Rectangle& rect)
                               :m_leftUp{new Point(*rect.m_leftUp)},//Point(*rect.m_leftUp)调用拷贝构造函数生成Point类型的对象
                                m_length{rect.m_length},
                                m_width{rect.m_width}
    {

    }
                                
};
    int Rectangle::getfunction()//如果想要实现A.getfunction(B)的话，需要在左侧函数括号里面加上形参
  {
      std::cout<<"Output m_length="<<m_length<<std::endl;
      std::cout<<"Output m_width="<<m_width<<std::endl;
      std::cout<<"Output Point.x="<<(*m_leftUp).x<<std::endl;//通过两层的递进关系，实现取出最底层的函数数据
      std::cout<<"Output Point.y="<<(*m_leftUp).y<<std::endl;//通过两层的递进关系，实现取出最底层的函数数据
      return m_width;
  }
  class Bigclass
  {
      Rectangle R;
  };
        int main(int argc, char const *argv[])
        {
            /* code */
            // Rectangle A(1,2,3,4);
            // A.getfunction();
            return 0;
        }
