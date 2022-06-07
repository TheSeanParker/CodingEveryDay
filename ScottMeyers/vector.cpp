
#include "vect.hpp"
// VECTOR::Vector Max(const VECTOR::Vector& v1,const VECTOR::Vector& v2)
// {
//     if (v1.magval()>v2.magval())
//     {
//         return v1;
//     }
//     else  
//     return v2;
// }

//类的成员函数才允许在尾部加const，是对函数本身的修饰，表示函数的data是不可以修改的

const VECTOR::Vector& Max(const VECTOR::Vector& v1,const VECTOR::Vector& v2)
{
    v1.magval(); 
    return v2;
}
int main(int argc, char const *argv[])
{
    /* code */
    int x=2;
    const int& y=x;
    const int z=5;
    //int& c=z;
    VECTOR::Vector force1(50,60);
    VECTOR::Vector force2(10,70);
    VECTOR::Vector max;
    //max=Max(force1,force2);  
    std::cout<<max.magval();
    return 0;
}
