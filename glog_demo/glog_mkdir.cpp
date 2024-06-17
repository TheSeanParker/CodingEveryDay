
#include <iostream>
#include <glog/logging.h>
#include <cstdlib>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    // create logpath
    std::string str_des;
    str_des.append("mkdir -p ");
    str_des.append("log");
    system(str_des.c_str());
    std::cout<<"str_des.c_str()="<<str_des.c_str()<<std::endl;
    // INFO
    std::string str_info;
    str_info.append("./log");
    str_info.append("/INFO_");
    google::SetLogDestination(google::INFO, str_info.c_str());
    // WARNING
    std::string str_warn;
    str_warn.append("./log");
    str_warn.append("/WARNING_");
    google::SetLogDestination(google::WARNING, str_warn.c_str());
    LOG(WARNING) << "The is a warning!";
    // my own type
    std::string str_pro;
    str_pro.append("./log");
    str_pro.append("/PROFILE_");
    google::SetLogDestination(google::WARNING, str_pro.c_str());
    LOG(WARNING) << "The is my own type!";
    // stop glog
    google::ShutdownGoogleLogging();
}