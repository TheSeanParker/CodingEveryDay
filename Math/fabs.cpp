#include <math.h>
#include <iostream>
int main(int argc, char const *argv[])
{
    /* code */
    float a=2.01;
    float b=3.99;
    if(abs(a-b)> 1e-7)
       std::cout<<abs(a-b)<<">>>>>>";
    else  std::cout<<abs(a-b)<<"<<<<<";
    int c=3,d=1;
    std::cout<<"fabs(a-b)="<<fabs(c-d)<<std::endl;
    float range=13.98;
    double thread=9;
    bool A=true;
    bool B=true;
    bool C=true;
    bool D=false;
    bool E=(A || B || C &&D); //false
    std::cout<<"E="<<E<<std::endl;
    
    return 0;
}
