#include <iostream>
#include<vector>
using namespace std;
int abc(vector<int> &a)
{
  return a.back();
}
int main(int argc, char const *argv[])
{
    /* code */
    std::vector<int> test{1,2,3,4,5,6};
    int c;
    cin>>c;
    test.push_back(c);
    int b=test.at(2);
    cout<<"Output="<<b<<"\n";
    abc(test);
    cout<<"abc(test)="<<abc(test)<<"\n";
    return 0;
}
