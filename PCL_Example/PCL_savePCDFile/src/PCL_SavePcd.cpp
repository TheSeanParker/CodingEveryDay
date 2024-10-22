#include <pcl/io/pcd_io.h>
#include <pcl/common/impl/io.hpp>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
 
// using namespace std;
//  int main(int argc, char const *argv[])
//  {
//     pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
//     pcl::PointXYZ point1 = { 1, 1, 1};
//     pcl::PointXYZ point2 = { 2, 2, 2};
//     pcl::PointXYZ point3 = { -3, -3, -3};
//     //在索引号为5的位置1上插入一点，原来的点后移一位
//     // cloud->insert(cloud->begin() + 5, point);
//     cloud->push_back(point1); //从点云最后面插入一点
//     cloud->push_back(point2); //从点云最后面插入一点
//     cloud->push_back(point3); //从点云最后面插入一点
//     // std::cout << cloud->points[5].x;//输出1
//     cout<<"pcd size()="<<cloud->size();
//     pcl::io::savePCDFile("demo.pcd",*cloud);
//     return 0;
//  }
 using namespace std;
int main(int argc, char const *argv[])
{
    string ROOT_DIR_="/home/deploy/PCL_IO/PCL_savePCDFile";
     pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        for (size_t i = 1; i <= 4; i++)
        {
            pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_temp(new pcl::PointCloud<pcl::PointXYZ>);
            string all_points_dir(string(string(ROOT_DIR_) + "/scans_") + to_string(i) + string(".pcd"));
            pcl::PCDReader reader;
            reader.read(all_points_dir, *cloud_temp); //读取 子pcd
            *cloud +=  *cloud_temp;
        }

        string file_name = string("demo.pcd");
        string all_points_dir(string(string(ROOT_DIR_) + "/") + file_name);
        std::cout << "current Large scan saved to /PCD/" << file_name << endl;
        pcl::io::savePCDFile("demo.pcd",*cloud);
      //   pcd_writer.writeBinary(all_points_dir, *cloud);
    return 0;
}
