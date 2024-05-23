#include <vector>
#include <iostream>
using namespace std;
vector<double> mdTimestampsCam;
void fun(vector<double>& vdTimestampsCam)
{
          double abc=.12;
          double ab=.13;
          //  vdTimestampsCam.push_back(a);
           vdTimestampsCam.push_back(abc);
           vdTimestampsCam.push_back(ab);
           cout<<"vvvvvvvvvvvvvdTimestampsCam.size()="<<vdTimestampsCam.size()<<endl;
}
int main(int argc, char const *argv[])
{
          /* code */
          cout<<"argc="<<argc<<endl;
          cout<<"argv[0]="<<argv[0]<<endl;
          // cout<<"argv[1]="<<argv[1]<<endl;
          // cout<<"argv[2]="<<argv[2]<<endl;
          // double a=2;
          vector<double> ab;
          fun(mdTimestampsCam);
          cout<<"mmmmmmmdTimestampsCam.size()="<<mdTimestampsCam.size()<<endl;
          // cout<<"vdTimestampsCam.at(1)="<<vdTimestampsCam.at(1)<<endl;
          return 0;
}
