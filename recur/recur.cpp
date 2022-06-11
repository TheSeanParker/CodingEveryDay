// recur.cpp -- using recursion
#include <iostream>
void countdown(int n)
{
    using namespace std;
    cout <<"Counting down ... " << n << endl;
    if (n <= 0)
    {cout<<"test***********"<<endl;}
    else
    {
        cout << n << ": cut in else()\n";
        countdown(n-2); //function calls itself
        cout << n << ": Kaboom!\n";
    }       
    //cout << n << ": Kaboom!\n";
}
int main()
{
    countdown(4);       // call the recursive function
    // std::cin.get();
    return 0;
}
//Counting down ...4
//Counting down ...2
//Counting down ...0
//test***********
//这里面之所以没有打印出0，是因为它压根没有进栈，进到递归循环里面才算进栈
//2 : Kaboom!
//4 : Kaboom!
