#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/registration/correspondence_estimation.h>
#include <boost/thread/thread.hpp>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/registration/transformation_estimation_svd.h> 
#include <pcl/registration/gicp.h>
#include <pcl/console/time.h>
#include <pcl/features/fpfh_omp.h>  
#include <pcl/keypoints/iss_3d.h>
#include <pcl/registration/ia_ransac.h>

using namespace std;

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;
void extract_keypoint(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& keypoint)//ISS关键点提取
{
	pcl::ISSKeypoint3D<pcl::PointXYZ, pcl::PointXYZ> iss;
	pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints(new pcl::PointCloud<pcl::PointXYZ>());
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
	iss.setInputCloud(cloud);
	iss.setSearchMethod(tree);
	iss.setNumberOfThreads(8);     //初始化调度器并设置要使用的线程数
	iss.setSalientRadius(5);  // 设置用于计算协方差矩阵的球邻域半径
	iss.setNonMaxRadius(5);   // 设置非极大值抑制应用算法的半径
	iss.setThreshold21(0.95);     // 设定第二个和第一个特征值之比的上限
	iss.setThreshold32(0.95);     // 设定第三个和第二个特征值之比的上限
	iss.setMinNeighbors(6);       // 在应用非极大值抑制算法时，设置必须找到的最小邻居数
	iss.compute(*keypoint);
	//cout << "ISS_3D points 的提取结果为 " << keypoint->points.size() << endl;
}
pcl::PointCloud<pcl::FPFHSignature33>::Ptr compute_fpfh_feature(pcl::PointCloud<pcl::PointXYZ>::Ptr& keypoint)
{
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	n.setInputCloud(keypoint);
	n.setSearchMethod(tree);
	n.setKSearch(10);
	n.compute(*normals);
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfh(new pcl::PointCloud<pcl::FPFHSignature33>);
	pcl::FPFHEstimationOMP<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> f;
	f.setNumberOfThreads(8);
	f.setInputCloud(keypoint);
	f.setInputNormals(normals);
	f.setSearchMethod(tree);
	f.setRadiusSearch(50);
	f.compute(*fpfh);

	return fpfh;
}
//sac粗配准
pcl::PointCloud<pcl::PointXYZ>::Ptr sac_align(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr s_k, pcl::PointCloud<pcl::PointXYZ>::Ptr t_k, pcl::PointCloud<pcl::FPFHSignature33>::Ptr sk_fpfh, pcl::PointCloud<pcl::FPFHSignature33>::Ptr tk_fpfh)
{
	pcl::SampleConsensusInitialAlignment<pcl::PointXYZ, pcl::PointXYZ, pcl::FPFHSignature33> scia;
	scia.setInputSource(s_k);
	scia.setInputTarget(t_k);
	scia.setSourceFeatures(sk_fpfh);
	scia.setTargetFeatures(tk_fpfh);
	scia.setMinSampleDistance(7);///参数：设置采样点之间的最小距离，满足的被当做采样点
	scia.setNumberOfSamples(50);////设置每次迭代设置采样点的个数(这个参数多可以增加配准精度)
	scia.setCorrespondenceRandomness(6);//设置选择随机特征对应点时要使用的邻域点个数。值越大，特征匹配的随机性就越大
	pcl::PointCloud<pcl::PointXYZ>::Ptr sac_result(new pcl::PointCloud<pcl::PointXYZ>);
	scia.align(*sac_result);
	pcl::transformPointCloud(*cloud, *sac_result, scia.getFinalTransformation());
	return sac_result;
}
//// 点云可视化
//void visualize_pcd(PointCloud::Ptr pcd_src, PointCloud::Ptr pcd_tgt, PointCloud::Ptr pcd_final)
//{
//	//创建初始化目标
//	pcl::visualization::PCLVisualizer viewer("registration Viewer");
//	pcl::visualization::PointCloudColorHandlerCustom<PointT> src_h(pcd_src, 0, 255, 0);//绿色
//	pcl::visualization::PointCloudColorHandlerCustom<PointT> tgt_h(pcd_tgt, 255, 0, 0);//红色
//	pcl::visualization::PointCloudColorHandlerCustom<PointT> final_h(pcd_final, 0, 0, 255);//蓝色
//	viewer.setBackgroundColor(255, 255, 255);
//	viewer.addPointCloud(pcd_src, src_h, "source cloud");
//	viewer.addPointCloud(pcd_tgt, tgt_h, "tgt cloud");
//	viewer.addPointCloud(pcd_final, final_h, "final cloud");
//
//	while (!viewer.wasStopped())
//	{
//		viewer.spinOnce(100);
//		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
//	}
//}
int main(int argc, char** argv)
{
	system("color F0");
    pcl::console::TicToc time;

	// 加载点云文件
	PointCloud::Ptr source(new PointCloud);    // 源点云，待配准
	pcl::io::loadPCDFile("pig_view1.pcd", *source);
	PointCloud::Ptr target(new PointCloud);    // 目标点云
	pcl::io::loadPCDFile("pig_view2.pcd", *target);
	PointCloud::Ptr key_src(new PointCloud);
	PointCloud::Ptr key_tgt(new PointCloud);
	extract_keypoint(source, key_src);//ISS关键点提取
	cout << "源点云的关键点提取结果为 " << key_src->points.size() << endl;
	extract_keypoint(target, key_tgt);
	cout << "目标点云的关键点提取结果为 " << key_tgt->points.size() << endl;
	////粗配准
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr sk_fpfh = compute_fpfh_feature(key_src);
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr tk_fpfh = compute_fpfh_feature(key_tgt);
	pcl::PointCloud<pcl::PointXYZ>::Ptr result(new pcl::PointCloud<pcl::PointXYZ>);
	result = sac_align(source, key_src, key_tgt, sk_fpfh, tk_fpfh);
	
	////gicp配准
	time.tic();
	pcl::GeneralizedIterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> gicp;//初始化gicp对象
    gicp.setInputSource(result);//设置输入点云
    gicp.setInputTarget(target);//设置目标点云（输入点云进行仿射变换，得到目标点云）
    gicp.setMaxCorrespondenceDistance(100);//设置对应点对间的最大距离
    gicp.setTransformationEpsilon(1e-6);//为终止条件设置最小转换差异
    gicp.setEuclideanFitnessEpsilon(0.1);//设置收敛条件是均方误差和小于阈值，停止迭代
    gicp.setMaximumIterations(35);//设置最大迭代次数

    pcl::PointCloud<pcl::PointXYZ>::Ptr gicp_cloud(new pcl::PointCloud<pcl::PointXYZ>);//变换后的点云
    gicp.align(*gicp_cloud);

    cout << "Applied" << 35 << "GICP iterations in " << time.toc() / 1000 << "s" << endl;
    cout << "\nGICP has converged,score is" << gicp.getFitnessScore() << endl;
    cout << "变换矩阵为：\n" << gicp.getFinalTransformation() << endl;
    pcl::transformPointCloud(*result, *gicp_cloud, gicp.getFinalTransformation());

    boost::shared_ptr<pcl::visualization::PCLVisualizer>viewer(new pcl::visualization::PCLVisualizer("PCL Viewer"));
    viewer->setBackgroundColor(255, 255, 255);  
    //// 对目标点云着色可视化 (red).
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>target_color(target, 255, 0, 0);//红色
    viewer->addPointCloud<pcl::PointXYZ>(target, target_color, "target cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "target cloud");
    // 对源点云着色可视化 (green).
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>input_color(source, 0, 255, 0);//绿色
    viewer->addPointCloud<pcl::PointXYZ>(source, input_color, "input cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "input cloud");
    // 对输出点云着色可视化 (blue).
    //pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>output_color(gicp_cloud, 0, 0, 255);//蓝色
    //viewer->addPointCloud<pcl::PointXYZ>(gicp_cloud, output_color, "output cloud");
    //viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "output cloud");

    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }

    return 0;
}