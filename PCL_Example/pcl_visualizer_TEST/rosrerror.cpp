
#include <ros/ros.h>
#include <ros/console.h>
#include<iostream>
using namespace std;
void print(int b)
{
    int a=b;
    cout<<"output="<<a<<endl;
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "lio_sam");
    int b=9;
     print(b);
    ROS_INFO("\033[1;32m----> Map Optimization Started---------------------.\033[0m");
    ros::spin();

    return 0;
}
