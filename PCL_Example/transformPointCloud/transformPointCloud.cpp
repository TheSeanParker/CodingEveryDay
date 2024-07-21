#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/registration/registration.h>
#include <pcl/registration/icp.h>  
#include <iostream>
#include <pcl/common/transforms.h> 
using namespace std;
typedef pcl::PointXYZI PointType;

    Eigen::Affine3f trans2Affine3f(float transformIn[])
    {
        return pcl::getTransformation(transformIn[3], transformIn[4], transformIn[5], transformIn[0], transformIn[1], transformIn[2]);
    }
int main(int argc, char const *argv[])
{
       pcl::IterativeClosestPoint<PointType, PointType> icp;
       float transformInTheWorld[6];

       pcl::PointCloud<PointType>::Ptr laserCloudsource(new pcl::PointCloud<PointType>());
       pcl::PointCloud<PointType>::Ptr laserCloudFirstCLoud2(new pcl::PointCloud<PointType>());
       pcl::io::loadPCDFile("/home/deploy/PCL_Example/NDT/laserCloudsource.pcd",     *laserCloudsource);
       pcl::io::loadPCDFile("/home/deploy/PCL_Example/NDT/laserCloudFirstCLoud2.pcd",   *laserCloudFirstCLoud2);

        for (size_t i = 0; i < 6; i++)
        {
            transformInTheWorld[i]=0;
        }

        transformInTheWorld[2]=1.57;
        transformInTheWorld[3]=5;

        pcl::PointCloud<PointType>::Ptr transform(new pcl::PointCloud<PointType>());
        std::cout <<"transformInTheWorld[2] yaw="   <<transformInTheWorld[2]<<std::endl;    
        std::cout <<"transformInTheWorld[3] init_x="<<transformInTheWorld[3]<<std::endl;    

        icp.setMaxCorrespondenceDistance(100);
        icp.setMaximumIterations(100);
        icp.setTransformationEpsilon(1e-6);
        icp.setEuclideanFitnessEpsilon(1e-6);
        icp.setRANSACIterations(0);
        icp.setInputSource(laserCloudsource);
        icp.setInputTarget(laserCloudFirstCLoud2);

        Eigen::Affine3f thisPose6DInWorld = trans2Affine3f(transformInTheWorld);
        // icp.align(*transform, thisPose6DInWorld.matrix());  //初始配准只接受4*4的矩阵初始变换姿态
        cout<<"thisPose6DInWorld.matrix()=\n"<<thisPose6DInWorld.matrix()<<endl;
        // Call the registration algorithm which estimates the transformation and returns the transformed source (input) as output. 
        // pcl::io::savePCDFileASCII("/home/deploy/PCL_Example/NDT/transform.pcd",*transform);
        // std::cout << "After align():  ndt.getFitnessScore()=   "<<icp.getFitnessScore()<<std::endl;
        ////////////////////////////////////////////////////////////
        pcl::PointCloud<PointType>::Ptr TranslaserCloudCornerLast(new pcl::PointCloud<PointType>());
        pcl::transformPointCloud(*laserCloudsource, *TranslaserCloudCornerLast, thisPose6DInWorld); 
        pcl::io::savePCDFileASCII("/home/deploy/PCL_Example/NDT/transformPointCloud.pcd",*TranslaserCloudCornerLast);
           return 0;
}
