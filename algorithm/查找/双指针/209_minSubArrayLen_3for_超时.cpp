
#include<vector>
#include<iostream>
using namespace std;
int minSubArrayLen(int target, vector<int>& nums) {

int length=0;
for (size_t k = 0; k < nums.size(); k++)
{
    cout<<"first for() length="<<length<<";k="<<k<<endl;
    for (size_t i = 0; (i < nums.size()-length); i++)
    {
        int sum=0;
        cout<<"second for() "<<"sum="<<sum<<";nums[i]="<<nums[i]<<";i="<<i<<endl;
        for (size_t j = i; (j <= i+length); j++)
        {
            sum=sum+nums[j];
            if (sum >= target)
            {
                return length+1;
            } 
        }
    }
    length++;
}
   return 0;

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
