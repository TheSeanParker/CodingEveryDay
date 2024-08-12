#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vc;
    cout<<"size:"<<vc.size()<<" capacity:"<<vc.capacity()<<endl;
    for(int i=0; i<17; ++i)
    {
        vc.push_back(i);
        cout<<"size:"<<vc.size()<<" capacity:"<<vc.capacity()<<endl;
    }
    return 0;
}

