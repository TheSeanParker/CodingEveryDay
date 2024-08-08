#include<iostream>
#include<thread>
using namespace std;
void process()
{
    cout<<"cut in process()"<<endl;
}
int main(int argc, char **argv)
{
    cout<<"cut in main()"<<endl;
    std::thread mapping_process{process};
    cout<<"end"<<endl;
    mapping_process.join();
	return 0;
}