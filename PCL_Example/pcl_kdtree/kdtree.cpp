#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/search/kdtree.h> // 包含kdtree头文件
#include<iomanip>
#include<math.h>
typedef pcl::PointXYZ PointT;
using namespace std;
float pointDistance(PointT p1, PointT p2)
{
    return ((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
}
int main()
{
    pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
    pcl::io::loadPCDFile("GlobalMap.pcd", *cloud);

    // 定义KDTree对象
    pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
    kdtree->setInputCloud(cloud); // 设置要搜索的点云，建立KDTree

    std::vector<int> indices; // 存储查询近邻点索引
    std::vector<float> distances; // 存储近邻点对应距离的平方
    PointT point =cloud->points[0]; // 初始化一个查询点
    // 查询距point最近的k个点
    int k = 10;
    int size = kdtree->nearestKSearch(point, k, indices, distances);
    std::cout << "nearestKSearch point size():=" << size << std::endl;
    std::cout << "***************************************** " << std::endl;
    // 判断一下查询到的第一个点和给定的第一个点,是不是同一个点
    // 下面的for循环最好是使用返回的size，但是用k的话，会出现访问点云点下标超过找到点云点个数的情况
    size_t count=k;

    for (size_t i = 0; i < count; i++)
    {
       std::cout << "nearestKSearch  distances["<<i<<"]= " << distances[i]<< std::endl;
    }
    std::cout << "***************************************** " << std::endl;
    for (size_t i = 0; i < count; i++)
    {
       std::cout << "nearestKSearch  indices["<<i<<"]= " << indices[i]<< std::endl;
    }
    std::cout << "***************************************** " << std::endl;
    // for (size_t i = 0; i < count; i++)
    // {
    //    std::cout << "nearestKSearch radiusSearchfirst cloud->points[indices["<<i<<"]]= " << cloud->points[indices[i]]<< std::endl;
    // }
    
    float distances_01=pointDistance(cloud->points[0],cloud->points[indices[1]]);
    std::cout <<setprecision(12)<< "distances_01= " << distances_01<< std::endl;

    float distances_02=pointDistance(cloud->points[0],cloud->points[indices[2]]);
    std::cout <<setprecision(12)<< "distances_02= " << distances_02<< std::endl;

    std::cout << "nearestKSearch point indices(1)= " << indices[1] << std::endl;
    std::cout << "nearestKSearch point indices(2)= " << indices[2] << std::endl;
    // 查询point半径为radius邻域球内的点
    double radius = 2.0;
    size = kdtree->radiusSearch(point, radius, indices, distances);
    std::cout << "radiusSearch point size(): " << size << std::endl;
     // 判断一下查询到的第一个点和给定的第一个点,是不是同一个点
    std::cout << "radiusSearch cloud->points[0]= " << cloud->points[0]<< std::endl;
    std::cout << "radiusSearch first point indices(0)= " << indices[0] << std::endl;
    std::cout << "radiusSearch second point indices(1)= " << indices[1]<< std::endl;
    std::cout << "radiusSearch second point indices(2)= " << indices[2]<< std::endl;
    // system("pause");
    return 0;
}