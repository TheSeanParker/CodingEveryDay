#include<iostream>
#include<climits>
int maxW=INT_MAX;
int weight[] ={2,2,4,6,3};
int n=5;
int w=9;
void fun(int i,int cw)
{
  if (cw==w||i==n)
  {
      if (cw>maxW)
      {
        maxW=cw;
      } 
  }
  fun(i+1,cw);//不装第i个物品
  if (cw+weight[i]<=w)
  {
  fun(i+1,cw+weight[i]);//装第i个物品
  }
}
int main(int argc, char const *argv[])
{
    fun(3,9);
    return 0;
}
