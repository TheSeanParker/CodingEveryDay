#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/ndt.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <pcl/filters/filter.h>
using namespace std;
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

// 进行处理NDT算法
  //初始化正态分布变换（NDT）
  pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt;
  // 设置依赖尺度NDT参数
  // 为终止条件设置最小转换差异
  ndt.setTransformationEpsilon (0.01);
  //为More-Thuente线搜索设置最大步长(先是大步长,然后小步长迭代)
  ndt.setStepSize (0.1);
  //设置NDT网格结构的分辨率（VoxelGridCovariance）
  ndt.setResolution (1.0);
  //设置匹配迭代的最大次数
  ndt.setMaximumIterations (35);
  // 设置要配准的点云(设置需配准的点云)
  // ndt.setInputCloud (filtered_cloud);
  ndt.setInputCloud (filtered_cloud_notfinite);// scan2.pcd
  //设置点云配准目标
  ndt.setInputTarget (target_cloud);
  std::cout << "setInputTarget()" <<std::endl;
  //设置使用机器人测距法得到的初始对准估计结果
  // 问题可能是出现在了,下面,下面的内容是对于特定点云是对的,但不具备普世性
  Eigen::AngleAxisf init_rotation (0.6931, Eigen::Vector3f::UnitZ ());
  Eigen::Translation3f init_translation (1.79387, 0.720047, 0);
  Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix ();
  //计算需要的刚体变换以便将输入的点云匹配到目标点云
  pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  std::cout << "init_rotation.matrix()="<< init_rotation.matrix()<<std::endl;
  // ndt.align (*output_cloud, init_guess); // 经过初始变换后,输出对应的点云
  ndt.align (*output_cloud); // 不用初始对准进行NDT匹配
  std::cout << "Normal Distributions Transform has converged: \n" << ndt.hasConverged ()
                     << " score: " << ndt.getFitnessScore () << std::endl;
  //使用创建的变换对未过滤的输入点云进行变换
  std::cout << "ndt.getFinalTransformation ()=\n"<<ndt.getFinalTransformation()<<std::endl;// 就是初始变换
  pcl::transformPointCloud(*input_cloud, *output_cloud, ndt.getFinalTransformation ());
  //保存转换的输入点云
  pcl::io::savePCDFileASCII ("room_scan2_transformed.pcd", *output_cloud);
  // 初始化点云可视化界面
  boost::shared_ptr<pcl::visualization::PCLVisualizer>
  viewer_final (new pcl::visualization::PCLVisualizer ("3D Viewer"));// PCD窗口显示的名称
  viewer_final->setBackgroundColor (0, 0, 0);
  //对目标点云着色（红色）并可视化
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
  target_color (target_cloud, 255, 0, 0);
  viewer_final->addPointCloud<pcl::PointXYZ> (target_cloud, target_color, "target cloud");
  viewer_final->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE,1, "target cloud");
  //对转换后的目标点云着色（绿色）并可视化
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
  output_color (output_cloud, 0, 255, 0);
  viewer_final->addPointCloud<pcl::PointXYZ> (output_cloud, output_color, "output cloud");
  viewer_final->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
                                                  1, "output cloud");
  // 启动可视化
  viewer_final->addCoordinateSystem (1.0);
  viewer_final->initCameraParameters ();
  //等待直到可视化窗口关闭。
  while (!viewer_final->wasStopped ())
  {
    viewer_final->spinOnce (100);
    boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }
  return (0);
}
