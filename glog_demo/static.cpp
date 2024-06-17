#include <iostream>
#include <glog/logging.h>  
using namespace std;
//声明全局变量
int n=3;
static int j=5;
//static变量的作用域<=生存周期
void testStatic()
{
    // 声明局部变量
    int m=3;
    static int i=5;
}
int foo() {
    static int count = 0;  // static 修饰局部变量
    count++;
    cout << count << endl;
    return count;
}

void func()
{

}

int main(int argc, char **argv) {
    // 初始化google的日志库
    google::InitGoogleLogging("static");  
    // 设置特定严重级别的日志的输出目录和前缀。
    // 第一个参数为日志级别，第二个参数表示输出目录及日志文件名前缀
    google::SetLogDestination(google::GLOG_FATAL, "../log_/log_fatal_"); 
    google::SetLogDestination(google::GLOG_ERROR, "../log_Error/log_error_"); //设置 google::ERROR 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_WARNING, "../log_Warning/log_warning_"); //设置 google::WARNING 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_INFO, "../log_Info/log_info_"); //设置 google::INFO 级别的日志存储路径和文件名前缀
    // FLAGS_log_dir = "/home/deploy/static/log_";
    LOG(WARNING) << "static!";
    cout<<"output i="<<j<<endl;
    int J=foo();  // 输出 1
    LOG(INFO) << "J=" << J;  
    int L=foo();  // 输出 2
    LOG(INFO) << "L=" << L;  
    int U= foo();  // 输出 3
    LOG(INFO) << "U=" << U;  
    LOG(WARNING) << "The is a warning!";
    for (size_t i = 0; i < 2; i++)
    {
        static double timeLastProcessing = -1;
        // 比较上下2个代码的区别
        // double timeLastProcessing = -1;
        int timeLaserInfoCur=0;
        if (timeLaserInfoCur - timeLastProcessing >= 0.1)
        {
            timeLastProcessing = timeLaserInfoCur+i;
        }
        LOG(INFO) << "timeLastProcessing=" << timeLastProcessing; 
        // 0
        // 1
    }
    

    return 0;
}