#include <iostream>
class complex
{
public:
  complex (double r = 0, double i = 0): re (r), im (i) { }
  complex& operator += (const complex&);

  double real () const { return re; }
  double imag () const { return im; }
private:
  double re, im;

  friend complex& __doapl (complex *, const complex&);
};
inline complex& __doapl(complex* ths,const complex& r)
{
    ths->re +=r.re;
    ths->im +=r.im;
    return *ths;
}
inline complex& complex::operator+=(const complex& r)
{
    return __doapl(this,r);
}

inline double
real (const complex& x)
{
  return x.real ();
}
inline double
imag (const complex& x)
{
  return x.imag ();
}
inline bool
operator == (const complex& x, const complex& y)
{
  // std::cout<<"real(x)"<<real (x)<<std::endl;
  // std::cout<<"real(y)"<<real (y)<<std::endl;
  // std::cout<<"imag (x)"<<imag(x)<<std::endl;
  // std::cout<<"imag (x)"<<imag(x)<<std::endl;
  return real (x) == real (y) && imag (x) == imag (y);
}