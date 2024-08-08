#include<iostream>
#include<thread>
using namespace std;
void process()
{
    static int a=1;
    while (a<5)
    {
        a++;
        cout<<"cut in process() a="<<a<<endl;
    }   
}
int main(int argc, char **argv)
{
    cout<<"cut in main()"<<endl;
    std::thread mapping_process{process};
    cout<<"end"<<endl;
    mapping_process.join();
	return 0;
}