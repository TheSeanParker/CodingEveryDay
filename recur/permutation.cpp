#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
//下面算法的关键问题只有一个，就backtrack()函数是什么时候停止的？
class Solution 
{
public:
    int cnt=0;
    void backtrack(vector<vector<int> >& res, vector<int>& output, int first, int len)
    {
        // 所有数都填完了
        cout<<"第一次进入函数的************first="<<first<<endl;
        //为了防止无限递归，可以在一个分支进行递归调用而另一个不进行递归调用的情况下使用if ... else语句（或类似方法）
        if (first == len) 
        {
            std::cout<<"cut in if()"<<";if_first="<<first<<endl; 
            res.push_back(output);
            std::cout<<"res.size()="<<res.size()<<endl; 
            //return;//可加，可不加
        }
        for (int i = first; i < len; ++i) 
        {
            // 动态维护数组
            cout<<"backtrack i ="<<i<<";backtrack_first="<<first<<endl; 
            swap(output[i], output[first]);
            // 继续递归填下一个数 
            backtrack(res, output, first + 1, len);
            // 撤销操作
            swap(output[i], output[first]);
            cout<<"swap i ="<<i<<";swap_first="<<first<<endl;
            //此步奏和递归循环在同一个循环体里面，所以会后退(n-1)步
            //回退(n-1)步骤以后，将会执行for循环里面的++i
        }
        std::cout<<"quit on "<<cnt++<<endl; 
    }
    vector<vector<int>> permute(vector<int>& nums) 
    {
        vector<vector<int>> res;
        cout<<"nums.size()="<<nums.size()<<";(int)nums.size()="<<(int)nums.size()<<std::endl;
        backtrack(res, nums, 0, (int)nums.size());
        cout<<"permute end"<<endl;
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
    
