#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <string_view>
 
int main()
{
    std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    //std::sort(s.begin(), s.end());
    printf("sorted with the default operator<");
    std::cout<<"\n"<<"s[2]="<<s[2]<<std::endl;
    struct 
    {
        bool operator()(int a, int b) const { return a >b; }
    } customLess;
    std::sort(s.begin(), s.end(), customLess);
    std::cout<<"\n"<<"s[2]="<<s[2]<<std::endl;
    printf("sorted with a custom function object");
}