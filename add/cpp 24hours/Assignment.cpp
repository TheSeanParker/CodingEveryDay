#include <iostream>
  
int main()
{
    int a=1;
    std::cout << "a:\t"  << &a << "\n";
    int b=a;
    std::cout << "a:\t"  << &a << "\n";
    std::cout << "b:\t"  << &b << "\n";

    int intOne;
    int &rSomeRef = intOne;
  
    intOne = 5;
    std::cout << "intOne:\t" << intOne << "\n";
    std::cout << "rSomeRef:\t" << rSomeRef << "\n";
    std::cout << "&intOne:\t"  << &intOne << "\n";
    std::cout << "&rSomeRef:\t" << &rSomeRef << "\n";
  
    int intTwo = 8;
    rSomeRef = intTwo; // not what you think!
    std::cout << "\nintOne:\t" << intOne << "\n";
    std::cout << "intTwo:\t" << intTwo << "\n";
    std::cout << "rSomeRef:\t" << rSomeRef << "\n";
    std::cout << "&intOne:\t"  << &intOne << "\n";
    std::cout << "&intTwo:\t"  << &intTwo << "\n";
    std::cout << "&rSomeRef:\t" << &rSomeRef << "\n";
    return 0;
    /*
    5
    5
    地址1
    地址1
    5(错)8
    8
    8
    地址1
    地址2
    地址2(错)地址1
    */
}
