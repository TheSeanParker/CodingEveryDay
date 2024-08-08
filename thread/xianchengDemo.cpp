
#include <thread>
#include<iostream>
#include<chrono>
using namespace std;
//多线程需要对应的库进行链接才能编译
void download1()
{
    cout << "开始下载第一个视频..." << endl;
    for (int i = 0; i < 100; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        cout << "111111111111/////////////////////////////////////////:" << i << endl;
    }
    cout << "第一个视频下载完成..." << endl;
}

void download2()
{
    cout << "开始下载第2个视频..." << endl;
    for (int i = 0; i < 100; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        cout << "第2个视频下载进度**********************************:" << i << endl;
    }
    cout << "第2个视频下载完成..." << endl;
}
void process()
{
    cout << "------------------------------------" << endl;
}

int main()
{
    cout << "主线程开始运行\n";
    std::thread d2(download2);
    download1();
    d2.join();//谁调用此方法就让调用此方法的线程进入阻塞状态,等待执行完毕,再去执行其他方法!
     process();
}