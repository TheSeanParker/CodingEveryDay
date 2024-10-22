#include <string>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
using namespace std;
int main(int argc, char const *argv[])
{
    string ROOT_DIR_="/home/deploy/PCL_IO/";
     pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        for (size_t i = 1; i <= 4; i++)
        {
            pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_temp(new pcl::PointCloud<pcl::PointXYZ>);
            string all_points_dir(string(string(ROOT_DIR_) + "/scans_") + to_string(i) + string(".pcd"));
            pcl::PCDReader reader;
            reader.read(all_points_dir, *cloud_temp); //读取 子pcd
            *cloud +=  *cloud_temp;
        }

        string file_name = string("GlobalMap.pcd");
        string all_points_dir(string(string(ROOT_DIR_) + "/") + file_name);
        pcl::PCDWriter pcd_writer;
        std::cout<<" PCDWriter cloud->size()="<<cloud->size()<<std::endl;
        std::cout << "current Large scan saved to /PCD/" << file_name << endl;
        pcd_writer.writeBinary(all_points_dir, *cloud);
        std::cout<<" savePCDFile cloud->size()="<<cloud->size()<<std::endl;
        string file_name_savePCDFile = string("demo.pcd");
        string all_points_savePCDFile(string(string(ROOT_DIR_) + "/") + file_name_savePCDFile);
        pcl::io::savePCDFile(all_points_savePCDFile,*cloud);
    return 0;
}
