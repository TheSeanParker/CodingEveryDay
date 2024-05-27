#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <pcl/filters/filter.h>
// 同样用ICP进行初始对准,效果明显不如NDT
int main (int argc, char** argv)
{
  //加载房间的第一次扫描
  pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ> ("room_scan1.pcd", *target_cloud) == -1)
  {
    PCL_ERROR ("Couldn't read file room_scan1.pcd \n");
    return (-1);
  }
  std::cout << "Loaded " << target_cloud->size () << " data points from room_scan1.pcd" << std::endl;
  //加载从新视角得到的房间的第二次扫描
  pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ> ("room_scan2.pcd", *input_cloud) == -1)
  {
    PCL_ERROR ("Couldn't read file room_scan2.pcd \n");
    return (-1);
  }
  std::cout << "Loaded " << input_cloud->size () << " data points from room_scan2.pcd" << std::endl;
  // 将输入的扫描过滤到原始尺寸的大概10%以提高匹配的速度。
  // 近似栅格的中心作为降采样坐标的近似
  pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  
  pcl::ApproximateVoxelGrid<pcl::PointXYZ> approximate_voxel_filter;
  approximate_voxel_filter.setLeafSize (0.2, 0.2, 0.2);
  approximate_voxel_filter.setInputCloud (input_cloud);
  approximate_voxel_filter.filter (*filtered_cloud);
  std::cout << "Filtered cloud contains " << filtered_cloud->size ()
                     << " data points from room_scan2.pcd" << std::endl;
  size_t filter_num=(*filtered_cloud).size();
  cout<<"filter_num="<<filter_num<<endl;

  // 下面是去除infinite点的过程,否则匹配时候会报错,这是基本预处理过程
  pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud_notfinite (new pcl::PointCloud<pcl::PointXYZ>);
  // 方法1
  //  pcl::removeNaNFromPointCloud(*filtered_cloud, *filtered_cloud_notfinite);

  // 方法2
  for (size_t i = 0; i <filter_num; i++)
  {
        if (!pcl_isfinite(filtered_cloud->points[filter_num].x) || 
             !pcl_isfinite(filtered_cloud->points[filter_num].y) || 
             !pcl_isfinite(filtered_cloud->points[filter_num].z)) 
            continue;
       pcl::PointXYZ point;
       point.x=filtered_cloud->points[filter_num].x;
       point.y=filtered_cloud->points[filter_num].y;
       point.z=filtered_cloud->points[filter_num].z;
       filtered_cloud_notfinite->push_back(point);
  }
  int notinf=   filtered_cloud_notfinite->size();
  cout<<"notinf="<<notinf<<endl;

  Eigen::AngleAxisf init_rotation (0.6931, Eigen::Vector3f::UnitZ ());
  Eigen::Translation3f init_translation (1.79387, 0.720047, 0);
  Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix ();
  //计算需要的刚体变换以便将输入的点云匹配到目标点云
  std::cout << "init_rotation.matrix()="<< init_rotation.matrix()<<std::endl;

  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
  icp.setInputCloud(filtered_cloud_notfinite);
  icp.setInputTarget(target_cloud);

  pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  icp.align(*output_cloud, init_guess); // 经过初始变换后,输出对应的点云
  pcl::transformPointCloud(*input_cloud, *output_cloud, icp.getFinalTransformation ());
  pcl::io::savePCDFileASCII ("ICP_room_scan2_transformed.pcd", *output_cloud);

  std::cout << "has converged:" << icp.hasConverged() << " score: " <<icp.getFitnessScore() << std::endl;
  std::cout << icp.getFinalTransformation() << std::endl;
 return (0);
}
