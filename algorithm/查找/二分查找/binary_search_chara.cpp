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

int main(int argc, char const *argv[])
{
    vector<char> inputvec;
    int count=10;
    char temp;
    char target;
    cin>>target;
    for (size_t i = 0; i < count; i++)
    {
       cin>>temp;
       inputvec.push_back(temp);
    }

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
