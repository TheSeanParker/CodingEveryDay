#include <algorithm>
#include <functional>
#include <string>
#include <iostream>

//循环打印字符串
int main(int argc, char const *argv[])
{
    /* code */
    using namespace std;
    cout<<"Enter a word";
    string word;
    cin>>word;
    // display reverse
    for (int i = word.size()-1; i >=0; i--)//左侧一定是int 不能是size_t
    {
        /* code */
        cout<<word[i]<<";"<<std::endl;
    }
    return 0;
}
