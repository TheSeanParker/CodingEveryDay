#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vec{1,2,3,4,5};
    int size=vec.size();
    for (size_t i = size; i >0; i--)
    {
        vec.insert(vec.begin()+i,9);
    }

    for (size_t i =(vec.size()-1); i >0; i--)
    {
       cout<<"vec["<<i<<"]="<<vec[i]<<endl;
    }
      cout<<"vec["<<0<<"]="<<vec[0]<<endl;
    return 0;
}

