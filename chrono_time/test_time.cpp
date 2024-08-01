#include "tic_toc.h"
#include <iostream>
using namespace std;
#include<iostream>
#include<vector>
#include<string>
#include<ctime>//将时间格式的数据转换成字符串
#include<chrono>
using namespace std::chrono;
using namespace std;
int main(int argc, char const *argv[])
{
    TicToc a;
    cout<<"time="<<endl;
    a.toc();
    printf("&&&&&&&&&&&&&&&&&&& time_time_laserCloudInfoHandler = %f s \n", a.toc());
    TicToc c;
    auto sta=std::chrono::high_resolution_clock::now();
    auto tNow=high_resolution_clock::to_time_t(sta);
    std::cout<<"start time="<<tNow<<std::endl;
    auto end = std::chrono::system_clock::now();
    auto dur=std::chrono::duration<float>(end-sta);
    cout<<"程序花费的时间="<<dur.count()<<" "<<endl;
    return 0;
}
    // auto dur=std::chrono::duration_cast<microseconds>(end-sta);