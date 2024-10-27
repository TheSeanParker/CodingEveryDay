#include <iostream>
#include <map>
#include <vector>
using namespace std;
int main() {
	vector<int> vtr;
	//初始化容器
    if (vtr.begin()==vtr.end())
    {
      std::cout<<"0 容器为空"<<std::endl;
    }
	for (int i = 1; i < 2; ++i)
	{
		vtr.push_back(i);
	}
    if (vtr.begin()==vtr.end())
    {
      std::cout<<"1 容器为空"<<std::endl;
    }
    else
    {
        std::cout<<"1 容器不为空"<<std::endl;
    }
    
    std::cout<<"*vtr.begin="<<*vtr.begin()<<std::endl;
    std::cout<<"*vtr.end()="<<*(--vtr.end())<<std::endl;
    std::cout<<"*vtr.size()="<<vtr.size()<<std::endl;
    // auto pcl=vtr.end()--;
    // std::cout<<vtr.begin()<<std::endl;
    // if (vtr.begin()==pcl)
    // {
    //   std::cout<<"2 容器不为空"<<std::endl;
    // }
	//利用迭代器遍历容器
	cout << "方式1：";
	for (vector<int>::iterator it = vtr.begin(); it != vtr.end(); ++it)
	{
		cout << *it << " ";
	}
	// cout << "\n方式1：";
	// for (vector<int>::iterator it = begin(vtr); it != end(vtr); ++it)
	// {
	// 	cout << *it << " ";
	// }
	cout << endl;
}