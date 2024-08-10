#include<iostream>
#include<vector>
using namespace std;
int solution(const vector<char>& test,char& target_)
{
    for (size_t i = 0; i < test.size(); i++)
    {
        if (test[i]==target_)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    vector<char> inputvec;
    int count=10;
    char temp;
    char target;
    cin>>target;
    cout<<"输入待查完毕"<<endl;
    for (size_t i = 0; i < count; i++)
    {
       cin>>temp;
       inputvec.push_back(temp);
       cout<<"i="<<i<<endl;
       cout<<"inputvec.size()="<<inputvec.size()<<endl;
    }
    cout<<"输入字符串完毕"<<endl;
    for (size_t i = 0; i < count; i++)
    {
        cout<<inputvec[i];
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
