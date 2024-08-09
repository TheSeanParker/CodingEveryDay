#include<iostream>
#include <vector>
using namespace std;
void solution(const vector<char>& a)
{
    char resu_char;
    int max=0;
    for (size_t i = 0; i < a.size(); i++)
    {
        char ctemp=a[i];
        int num=1;
        for (size_t j = 0; j <i; j++)
        {
            if (ctemp==a[j])
            {
               num++;
            }
        }
        if (num>max)
        {
            resu_char=a[i];
        }
        max=(num>max)?num:max;    
    }
    std::cout<<"最多出现次数="<<max<<std::endl;
    std::cout<<"最多出现次数的字母="<<resu_char<<std::endl;
}

int main()
{
    vector<char> inputVec;
    char temp;
    size_t count=10;
    for (size_t i = 0; i < count; i++)
    {
        cin>>temp;
        inputVec.push_back(temp);
    }
    
    for (size_t i = 0; i < count; i++)
    {
        cout<<inputVec[i];
    }
    solution(inputVec);
}