#include <iostream>
#include <vector>
//bubble sort只涉及相邻数据的交换操作，常量级的临时空间即可。
//空间复杂度为O(1),是一个原地排序算法
using namespace std;
void bubble(vector<int>& a,int count)
{
   if (count<=1) return;
   for (size_t i = 0; i < count; i++)
   {
       bool flag=false;
       for (size_t j = 0; j< count-i-1; j++)
       {
           if (a[j]>a[j+1])
           {
               int temp=a[j];
               a[j]  =a[j+1];
               a[j+1]  =temp;
               flag=true;
           }
           
       }
       if(!flag) break;
   }   
}

int main(int argc, char const *argv[])
{

    vector<int> original;//容器是动态数据结构，可以一开始不声明容器大小。但是数组必须要
    cout<<"请输入数据:"<<endl;
    int str;
    std::cin>>str;//?r如何得到输入的长度，并进行计算？
    for (size_t i = 0; i < str.size(); i++)
    {
       original[i]=str[i];
    }
    int num=5;
    bubble(original, num);
    std::cout<<"original[2]="<<original[2]<<std::endl;
    std::cout<<"original[3]="<<original[3]<<std::endl;
    //cout<<"bubble size="<<sizeof(original)/sizeof(int)<<endl;//有没有其他方法获取数组的长度
    return 0;
}
