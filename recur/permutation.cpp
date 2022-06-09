
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
//下面算法的关键问题只有一个，就backtrack()函数是什么时候停止的？
class Solution 
{
public:
    void backtrack(vector<vector<int> >& res, vector<int>& output, int first, int len)
    {
        // 所有数都填完了
        cout<<"len="<<len<<endl;
        cout<<"first="<<first<<endl;
        if (first == len) 
        {
            std::cout<<"cut in if()"<<";if_first="<<first<<endl; 
            res.push_back(output);
            std::cout<<"res.size()="<<res.size()<<endl; 
            return;
        }
        for (int i = first; i < len; ++i) 
        {
            // 动态维护数组
            cout<<"交换i ="<<i<<";___first="<<first<<endl; 
            swap(output[i], output[first]);
            cout<<"*****************"<<endl;
            // 继续递归填下一个数
            cout<<"backtrack i ="<<i<<";backtrack_first="<<first<<endl; 
            backtrack(res, output, first + 1, len);
            // 这个recur被调用了n次数，那么将会引起recur()函数后面的所有函数撤退n-1次，不是n次？
            // 撤销操作
            cout<<"swap i ="<<i<<";swap_first="<<first<<endl; 
            swap(output[i], output[first]);//撤退完此步骤，为什么直接跳转到for循环下面呢?
        }
    }
    vector<vector<int>> permute(vector<int>& nums) 
    {
        vector<vector<int>> res;
        cout<<"nums.size()="<<nums.size()<<";(int)nums.size()="<<(int)nums.size()<<std::endl;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
    }
};
int main()
{
	int a[3]={1,2,3};
	vector<int>output(a,a+3);//这个写法，实在太好了;经典！将数组按指针赋值给了vector容器
	vector< vector<int>> res;
    Solution s;
	res=s.permute(output);//将每次得到的结果都塞到res里vector的vector里面
    //将他们遍历打印出来
	for(int i=0;i<res.size();i++){
			for(int j=0;j<res[i].size();j++)
	        	cout<<res[i][j]<<" ";
	    cout<<endl;
	}
	return 0;
}
    
