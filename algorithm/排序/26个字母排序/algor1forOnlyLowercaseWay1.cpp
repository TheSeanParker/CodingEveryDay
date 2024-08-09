#include<iostream>
#include <vector>
#include<algorithm>
// 使用数组记录字母出现的次数，用空间换时间
using namespace std;
void solution(const vector<char>& a)
{
    char resu_char;
    int record[26]={0};
    for (size_t i = 0; i < a.size(); i++)
    {
        record[a[i]-'a']++;
    }
    auto num=std::max_element(record,record+26);
    
    for (size_t i = 0; i < 26; i++)
    {
       if (*num==record[i])
       {
          resu_char=char(i+int('a'));
          std::cout<<"最多次数的小写字母="<<resu_char<<std::endl;
       }
    }
    std::cout<<"最多次数="<<*num<<std::endl;    
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