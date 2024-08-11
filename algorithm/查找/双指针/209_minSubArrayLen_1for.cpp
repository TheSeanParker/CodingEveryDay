
#include<vector>
#include<iostream>
using namespace std;
int minSubArrayLen(int target, vector<int>& nums) {

	int sum=0;
	int subLength = 0;
	int result = INT32_MAX;  // 或者 int result = numsSize + 1;
    int size=nums.size();
    int  j=0;
    for (size_t i = 0; i < size; i++)
    {
        sum+=nums[i];
        while (sum>=target)
        {
            subLength=i-j+1;
            result=(result>subLength)?subLength:result;
            sum-=nums[j++];
        }
    }
        result=(result==INT32_MAX)?0:result;
        return result;
        
}

int main(int argc, char const *argv[])
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
    int index=minSubArrayLen(target,inputvec);
    if (index==0)
    {
        std::cout<<"没找到"<<target<<std::endl;
    }
    else
    {
        std::cout<<"寻找到"<<target<<"的index="<<index<<std::endl;
    }
    return 0;
    return 0;
}
