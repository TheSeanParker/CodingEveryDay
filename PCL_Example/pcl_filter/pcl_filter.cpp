#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
// 包含相关头文件
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/uniform_sampling.h>

typedef pcl::PointXYZ PointT;

int main(int argc, char** argv)
{
    // 读取点云

    pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
    pcl::io::loadPCDFile(argv[1], *cloud);
    std::cout << "original cloud size : " << cloud->size() << std::endl;

    // 使用体素化网格(VoxelGrid)进行下采样
    pcl::VoxelGrid<PointT> grid; //创建滤波对象
    const float leaf = 4.f; 
    grid.setLeafSize(leaf, leaf, leaf); // 设置体素体积
    grid.setInputCloud(cloud); // 设置点云
    pcl::PointCloud<PointT>::Ptr voxelResult(new pcl::PointCloud<PointT>);
    grid.filter(*voxelResult); // 执行滤波，输出结果
    std::cout << "voxel downsample size :" << voxelResult->size() << std::endl;
    std::cout << "voxelResult->points[0]=:" << voxelResult->points[0]<< std::endl;
    std::cout << "voxelResult->points[1]=:" << voxelResult->points[1]<< std::endl;
    // 使用UniformSampling进行下采样
    pcl::UniformSampling<PointT> uniform_sampling;
    uniform_sampling.setInputCloud(cloud);
    double radius = 0.005f;
    uniform_sampling.setRadiusSearch(radius);
    pcl::PointCloud<PointT>::Ptr uniformResult(new pcl::PointCloud<PointT>);
    uniform_sampling.filter(*uniformResult);
    std::cout << "UniformSampling size :" << uniformResult->size() << std::endl;

    system("pause");
    return 0;
}