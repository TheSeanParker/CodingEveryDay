#include <iostream>
#include <vector>
using namespace std;
void printVector(vector<int>& vec)
{
      for (size_t i =0; i <(vec.size()); i++)
    {
       cout<<"vec["<<i<<"]="<<vec[i]<<endl;
    }
}
int main()
{
    // vector<int> vec{1,2,3,4,5};
    // int size=vec.size();
    // for (size_t i = size; i >0; i--)
    // {
    //     vec.insert(vec.begin()+i,9);
    // }
   // cout<<"vec["<<0<<"]="<<vec[0]<<endl;

 using PointVector = vector<int>;
  vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	vector<int> v2;
	v2.push_back(30);
	
	//printVector是自己编写用于遍历输出vector容器的函数
	printVector(v1);
	printVector(v2);
	
	v1.swap(v2);
	
	printVector(v1);
	printVector(v2);
  cout<<"--------------------------"<<endl;
 PointVector().swap(v1);
 printVector(v1);     
    return 0;
}

