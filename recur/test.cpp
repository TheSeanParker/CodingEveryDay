// recur.cpp -- using recursion
#include <iostream>
void countdown(int n)
{
    using namespace std;
    int x=3;
    if (n==x)
    {
       std::cout<<"res.size()="<<endl;
    }
    std::cout<<"**********"<<endl;
   
        countdown(n-1);
        
    
     std::cout<<"------------"<<endl;
}
int main()
{
    countdown(3);           // call the recursive function
    // std::cin.get();
    return 0;
}
