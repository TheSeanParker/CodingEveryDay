// recur.cpp -- using recursion
#include <iostream>
void countdown(int n)
{
    using namespace std;
    cout << "Counting down ... " << n << endl;
    if (n <= 0)
    {cout<<"test***********"<<endl;}
    else
    {
        countdown(n-2); //function calls itself
    }
    
            
    cout << n << ": Kaboom!\n";
}
int main()
{
    countdown(4);           // call the recursive function
    // std::cin.get();
    return 0;
}


