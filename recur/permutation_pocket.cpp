#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
//下面算法的关键问题只有一个，就backtrack()函数是什么时候停止的？
class Solution 
{
public:
    int cnt=0;
    void backtrack( int first)
    {
        cout<<"第一次进入函数的************first="<<first<<endl;
        if (first == 3) 
        {
            std::cout<<"cut in if()"<<";if_first="<<first<<endl; 
            //return;//可加，可不加
            //为什么有时候回退3个有时候2个，然后再是3个，这样循环着来呢？
        }
        for (int i = first; i < 3; ++i) 
        {
            cout<<"backtrack i ="<<i<<";backtrack_first="<<first<<endl; 
            backtrack(first + 1);
            cout<<"swap i ="<<i<<";swap_first="<<first<<endl; //i=1;first=1;
        }
        cout << "quit on " << cnt++ <<  endl;
    }
};
int main()
{
    Solution s;
	s.backtrack(0);
	return 0;
}
    
