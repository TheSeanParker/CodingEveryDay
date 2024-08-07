
#include <iostream>
#include <cassert>
int main(int argc, char const *argv[])
{
    int a=0;
    int b=2;
    for (size_t i = 0; i < 5; i++)
    {
           if (b>a)
            {
                a++;
                std::cout<<"new=\n";
            }
    }

    for (size_t i = 0; i < 5; i++)
    {
        std::cout<<"test=\n";
           if (b>a)
            {
                a++;
                std::cout<<"num=\n";
                assert(b>a);
            }
    }
    return 0;
}
