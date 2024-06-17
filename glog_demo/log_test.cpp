#include <iostream>
#include <glog/logging.h>  
int main(int argc, char **argv) {
    // 初始化google的日志库
    google::InitGoogleLogging(argv[0]);  
    // 设置特定严重级别的日志的输出目录和前缀。
    // 第一个参数为日志级别，第二个参数表示输出目录及日志文件名前缀
    google::SetLogDestination(google::GLOG_FATAL, "../log_/log_fatal_"); 
    google::SetLogDestination(google::GLOG_ERROR, "../log_Error/log_error_"); //设置 google::ERROR 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_WARNING, "../log_Warning/log_warning_"); //设置 google::WARNING 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_INFO, "../log_Info/log_info_"); //设置 google::INFO 级别的日志存储路径和文件名前缀
    // FLAGS_log_dir = "/home/deploy/static/log_";
    
    LOG(INFO) << "HELLO" << "ok!";  
    LOG(INFO) << "test" << "ok!";  
    LOG(WARNING) << "The is a warning!";
    // LOG(ERROR) << "Error occur";
    return 0;
}