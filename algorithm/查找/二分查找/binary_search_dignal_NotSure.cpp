#include<iostream>
#include<vector>
using namespace std;
int solution(const vector<int>& nums,int& target)
{
    int start=0;
        int end =nums.size();
        for (int i = start; i < end; i++)
        {
            if (nums[i]==target)
            {
                return i;
            }
            if (nums[end/2]<target)// 先假设整个队列的数目全是偶数
            {
                start=(end/2+1);
            }
            else
            {
                end=end/2+1;//这块是关键代码段！
            }
        }
         return -1;
}
int main()
{
    vector<int> inputvec;
    int count=6;
    int temp;
    int target;
    cin>>target;
    std::cout<<"输入待查数字完毕"<<endl;

    for (size_t i = 0; i < count; i++)
    {
       cin>>temp;
       inputvec.push_back(temp);
    }
    std::cout<<"输入数字串完毕"<<endl;

    for (size_t i = 0; i < count; i++)
    {
        std::cout<<inputvec[i];
    }
    int index=solution(inputvec,target);
    if (index==-1)
    {
        std::cout<<"没找到"<<target<<std::endl;
    }
    else
    {
        std::cout<<"寻找到"<<target<<"的index="<<index<<std::endl;
    }
    return 0;
}
