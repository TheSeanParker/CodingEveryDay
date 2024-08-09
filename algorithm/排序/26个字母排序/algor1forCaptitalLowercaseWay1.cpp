#include<iostream>
#include <vector>
#include<algorithm>
// 使用数组记录字母出现的次数，用空间换时间
using namespace std;
void solution(const vector<char>& a)
{
    char resu_char_lower;
    char resu_char_capital;
    vector<char>LowerRecord(26);
    vector<char>CapitaRecord(26);
    int recordLower[26]={0};
    int recordCapita[26]={0};
    int maxLower=0;
    int maxCapital=0;
    for (size_t i = 0; i < a.size(); i++)
    {
        if (int(a[i])>=97)
        {
            LowerRecord.push_back((a[i]));
        }
        else
        {
           CapitaRecord.push_back((a[i]));
        }    
    }
    
    for (size_t i = 0; i <LowerRecord.size() ; i++)
    {
        recordLower[LowerRecord[i]-'a']++;
    }

    for (size_t i = 0; i <CapitaRecord.size() ; i++)
    {
        recordCapita[CapitaRecord[i]-'A']++;
    }

    for (size_t i = 0; i < 26; i++)
    {
       if (recordLower[i]>maxLower)
       {
          maxLower=recordLower[i];
          resu_char_lower=char(i+int('a'));
       }
    }

    for (size_t i = 0; i < 26; i++)
    {
       if (recordCapita[i]>maxCapital)
       {
          maxCapital=recordCapita[i];
          resu_char_capital=char(i+int('A'));
       }
    }
    if (maxLower>maxCapital)
    {
        std::cout<<"\n最多小写字母次数="<<maxLower<<std::endl;    
        std::cout<<"最多次数的小写字母="<<resu_char_lower<<std::endl;
    }
    else if(maxLower<maxCapital)
    {
        std::cout<<"\n最多次数的大写字母="<<resu_char_capital<<std::endl;
        std::cout<<"最多大写字母次数="<<maxCapital<<std::endl;   
    }
    else
    {
        std::cout<<"\n最多小写字母次数和大写字母次数一样多"<<std::endl;   
        std::cout<<"最多小写字母次数="<<maxLower<<std::endl;    
        std::cout<<"最多次数的小写字母="<<resu_char_lower<<std::endl;
        std::cout<<"最多次数的大写字母="<<resu_char_capital<<std::endl;
        std::cout<<"最多大写字母次数="<<maxCapital<<std::endl;   
    }  
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