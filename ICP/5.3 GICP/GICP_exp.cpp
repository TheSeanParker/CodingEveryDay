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
void extract_keypoint(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& keypoint)//ISS�ؼ�����ȡ
{
	pcl::ISSKeypoint3D<pcl::PointXYZ, pcl::PointXYZ> iss;
	pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints(new pcl::PointCloud<pcl::PointXYZ>());
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
	iss.setInputCloud(cloud);
	iss.setSearchMethod(tree);
	iss.setNumberOfThreads(8);     //��ʼ��������������Ҫʹ�õ��߳���
	iss.setSalientRadius(5);  // �������ڼ���Э��������������뾶
	iss.setNonMaxRadius(5);   // ���÷Ǽ���ֵ����Ӧ���㷨�İ뾶
	iss.setThreshold21(0.95);     // �趨�ڶ����͵�һ������ֵ֮�ȵ�����
	iss.setThreshold32(0.95);     // �趨�������͵ڶ�������ֵ֮�ȵ�����
	iss.setMinNeighbors(6);       // ��Ӧ�÷Ǽ���ֵ�����㷨ʱ�����ñ����ҵ�����С�ھ���
	iss.compute(*keypoint);
	//cout << "ISS_3D points ����ȡ���Ϊ " << keypoint->points.size() << endl;
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
//sac����׼
pcl::PointCloud<pcl::PointXYZ>::Ptr sac_align(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr s_k, pcl::PointCloud<pcl::PointXYZ>::Ptr t_k, pcl::PointCloud<pcl::FPFHSignature33>::Ptr sk_fpfh, pcl::PointCloud<pcl::FPFHSignature33>::Ptr tk_fpfh)
{
	pcl::SampleConsensusInitialAlignment<pcl::PointXYZ, pcl::PointXYZ, pcl::FPFHSignature33> scia;
	scia.setInputSource(s_k);
	scia.setInputTarget(t_k);
	scia.setSourceFeatures(sk_fpfh);
	scia.setTargetFeatures(tk_fpfh);
	scia.setMinSampleDistance(7);///���������ò�����֮�����С���룬����ı�����������
	scia.setNumberOfSamples(50);////����ÿ�ε������ò�����ĸ���(������������������׼����)
	scia.setCorrespondenceRandomness(6);//����ѡ�����������Ӧ��ʱҪʹ�õ�����������ֵԽ������ƥ�������Ծ�Խ��
	pcl::PointCloud<pcl::PointXYZ>::Ptr sac_result(new pcl::PointCloud<pcl::PointXYZ>);
	scia.align(*sac_result);
	pcl::transformPointCloud(*cloud, *sac_result, scia.getFinalTransformation());
	return sac_result;
}
//// ���ƿ��ӻ�
//void visualize_pcd(PointCloud::Ptr pcd_src, PointCloud::Ptr pcd_tgt, PointCloud::Ptr pcd_final)
//{
//	//������ʼ��Ŀ��
//	pcl::visualization::PCLVisualizer viewer("registration Viewer");
//	pcl::visualization::PointCloudColorHandlerCustom<PointT> src_h(pcd_src, 0, 255, 0);//��ɫ
//	pcl::visualization::PointCloudColorHandlerCustom<PointT> tgt_h(pcd_tgt, 255, 0, 0);//��ɫ
//	pcl::visualization::PointCloudColorHandlerCustom<PointT> final_h(pcd_final, 0, 0, 255);//��ɫ
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

	// ���ص����ļ�
	PointCloud::Ptr source(new PointCloud);    // Դ���ƣ�����׼
	pcl::io::loadPCDFile("pig_view1.pcd", *source);
	PointCloud::Ptr target(new PointCloud);    // Ŀ�����
	pcl::io::loadPCDFile("pig_view2.pcd", *target);
	PointCloud::Ptr key_src(new PointCloud);
	PointCloud::Ptr key_tgt(new PointCloud);
	extract_keypoint(source, key_src);//ISS�ؼ�����ȡ
	cout << "Դ���ƵĹؼ�����ȡ���Ϊ " << key_src->points.size() << endl;
	extract_keypoint(target, key_tgt);
	cout << "Ŀ����ƵĹؼ�����ȡ���Ϊ " << key_tgt->points.size() << endl;
	////����׼
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr sk_fpfh = compute_fpfh_feature(key_src);
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr tk_fpfh = compute_fpfh_feature(key_tgt);
	pcl::PointCloud<pcl::PointXYZ>::Ptr result(new pcl::PointCloud<pcl::PointXYZ>);
	result = sac_align(source, key_src, key_tgt, sk_fpfh, tk_fpfh);
	
	////gicp��׼
	time.tic();
	pcl::GeneralizedIterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> gicp;//��ʼ��gicp����
    gicp.setInputSource(result);//�����������
    gicp.setInputTarget(target);//����Ŀ����ƣ�������ƽ��з���任���õ�Ŀ����ƣ�
    gicp.setMaxCorrespondenceDistance(100);//���ö�Ӧ��Լ��������
    gicp.setTransformationEpsilon(1e-6);//Ϊ��ֹ����������Сת������
    gicp.setEuclideanFitnessEpsilon(0.1);//�������������Ǿ�������С����ֵ��ֹͣ����
    gicp.setMaximumIterations(35);//��������������

    pcl::PointCloud<pcl::PointXYZ>::Ptr gicp_cloud(new pcl::PointCloud<pcl::PointXYZ>);//�任��ĵ���
    gicp.align(*gicp_cloud);

    cout << "Applied" << 35 << "GICP iterations in " << time.toc() / 1000 << "s" << endl;
    cout << "\nGICP has converged,score is" << gicp.getFitnessScore() << endl;
    cout << "�任����Ϊ��\n" << gicp.getFinalTransformation() << endl;
    pcl::transformPointCloud(*result, *gicp_cloud, gicp.getFinalTransformation());

    boost::shared_ptr<pcl::visualization::PCLVisualizer>viewer(new pcl::visualization::PCLVisualizer("PCL Viewer"));
    viewer->setBackgroundColor(255, 255, 255);  
    //// ��Ŀ�������ɫ���ӻ� (red).
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>target_color(target, 255, 0, 0);//��ɫ
    viewer->addPointCloud<pcl::PointXYZ>(target, target_color, "target cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "target cloud");
    // ��Դ������ɫ���ӻ� (green).
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>input_color(source, 0, 255, 0);//��ɫ
    viewer->addPointCloud<pcl::PointXYZ>(source, input_color, "input cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "input cloud");
    // �����������ɫ���ӻ� (blue).
    //pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>output_color(gicp_cloud, 0, 0, 255);//��ɫ
    //viewer->addPointCloud<pcl::PointXYZ>(gicp_cloud, output_color, "output cloud");
    //viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "output cloud");

    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }

    return 0;
}