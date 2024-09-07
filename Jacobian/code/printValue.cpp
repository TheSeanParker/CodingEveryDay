#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
  double x00=2;
  double x01=3;
  double xnew=10;
      for (size_t i = 0; i < 100; i++)
      {
          xnew=(x00/2+1/x00)*(-1);
          x00=x00+xnew;
          cout<<"xnew="<<xnew<<endl;
          cout<<"-------------x00="<<x00<<endl;
    }
    return 0;
}
