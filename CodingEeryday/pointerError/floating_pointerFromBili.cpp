#include <iostream>

int main(int argc, char const *argv[])
{
    /* code */
    int *pointer=nullptr;
    std::cout<<pointer<<std::endl;
    {int number=3;
    pointer =&number;}
    std::cout<<pointer<<std::endl;
    std::cout<<*pointer<<std::endl;
    return 0;
}
