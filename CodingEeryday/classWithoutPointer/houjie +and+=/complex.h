#ifndef __COMPLEX__
#define __COMPLEX__
class complex
{
public:
    complex(double r=0,double i=1)  
                 :re(r) ,im(i) { }
    complex& operator +=(const complex& );
    complex  operator + (const complex& x);//在类内重载操作符operator + （不推荐但可用）
    double real() const 
    {
      //++re;//  
      //上面这行之所以不可以是因为double real() const 中的cost，详细原因如下 
      //  int w=1;
      //  const int*  p=&w;
      //  *p=3;
      return re;
    }
    double imag() const {return im;}   
private:
    /* data */
    double re;
    double im;
    friend complex& __doapl (complex*, const complex&);//友元函数可以直接访问private函数
};
//inline function() ,若在函数体内定义完成，将自动成为inline()函数
  inline complex& __doapl(complex*ths,const complex& r) 
  {
    ths->re +=r.re;
    ths->im +=r.im;
    return *ths;
  }
  inline complex& complex::operator +=(const complex& r)//重载“+”运算符，进行运算，
  {   
      return __doapl (this ,r);
  }

//下面是real()函数的重载
  inline double real(const complex& x )
  {
       return x.real();
  }
  inline double imag(const complex& x )
  {
       return x.imag();
  }
  inline complex complex::operator+ (const complex& y)
  {
    return complex(this->re+y.real(),this->im+y.imag());
  }
//复数加上常数，这块设计在class的外面，才允许有4种形式的运算符？!
//二元运算符成员函数重载只能有一个参数或没有参数【因为this指针的存在】,所以没有办法进行4种变形的形式
  // inline complex operator +(const complex& x,double y)//注意和类内的 +=运算符重载作区分
  //操作符重载一定是作用在左侧的符号上面
  // {
  //   return complex(real(x)+y,imag(x));
  // }
  inline complex conj (const complex& x)
  {
    return complex (real(x),-imag(x));
  }
  #include <iostream>
  //只要在function外面都可以添加include语句以及命令
  //对于 operator<< 进行操作符重载不能在类内定义是，因为左侧是输出流，无法进行使用this指针
  //如果应要使用的话也是可以的，那样的话输入流的方向就是相反的了
  std::ostream& operator <<(std::ostream& os,const complex& x)
  {
    return os<<'('<<x.real()<<','<<imag(x)<<')';
  }
#endif