
#include<iostream>
#include <vector>
#include<algorithm>
// 使用数组记录字母出现的次数，用空间换时间
using namespace std;

void solution()
{
    char resu_char;
    static int record[26];
    for (size_t i = 0; i < 26; i++)
    {
       cout<<"print record["<<i<<"]="<<record[i]<<std::endl;
    }
    
}
int main(int argc, char const *argv[])
{
    solution();
    return 0;
}
