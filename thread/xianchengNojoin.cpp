
#include <thread>
#include<iostream>
#include<chrono>
using namespace std;
//多线程需要对应的库进行链接才能编译
void download1()
{
    cout << "开始下载第一个视频..." << endl;
    for (int i = 0; i < 100; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        cout << "下载进度1---------------------------111111111111111:" << i << endl;
    }
    cout << "第一个视频下载完成..." << endl;
}

void download2()
{
    cout << "开始下载第二个视频..." << endl;
    for (int i = 0; i < 100; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        cout << "下载进度22222222222222222222--------------:" << i << endl;
    }
    cout << "第二个视频下载完成..." << endl;
}
 void process()
 {
    cout<<"End="<<endl;
 }
int main()
{
    cout << "主线程开始运行\n";
    std::thread d2(download2);
    download1();
// download2();
    process();
}