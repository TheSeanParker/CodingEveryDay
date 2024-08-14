
#include <map>
#include <vector>
#include <set>
#include<iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    /* code */
    vector<int> ivec;
    for (size_t i = 0; i !=5; i++)
    {
      ivec.push_back(i);
      ivec.push_back(i);
    }
    set<int> iset(ivec.cbegin(),ivec.cend());
    multiset<int> miset(ivec.cbegin(),ivec.cend());
    multimap<int> mimap((ivec.cbegin(),ivec.cend()),"appel");

    cout<<"vector size()="<<ivec.size()<<endl;
    cout<<"set size()="<<iset.size()<<endl;
    cout<<"multiset size()="<<miset.size()<<endl;
    set<int>::iterator set_it =iset.begin();
    while (set_it!=iset.end())
    {
        cout<<" set output="<<*set_it<<endl;
        set_it++;
    }
    
    set<int>::iterator miset_it =miset.begin();
    while (miset_it!=miset.end())
    {
        cout<<" multiset output="<<*miset_it<<endl;
        miset_it++;
    }
    // 下面是错误示范：
    // for (size_t i = 0; i < iset.size(); i++)
    // {
    //     cout<<"iset["<<i<<"]="<<iset[i]<<endl;
    // }
    return 0;
}
