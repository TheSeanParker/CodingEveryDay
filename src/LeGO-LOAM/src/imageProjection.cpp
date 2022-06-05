// Copyright 2013, Ji Zhang, Carnegie Mellon University
// Further contributions copyright (c) 2016, Southwest Research Institute
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from this
//    software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "utility.h"


class ImageProjection{
private:

    ros::NodeHandle nh;//定义节点句柄

    ros::Subscriber subLaserCloud;//定义接受点云的订阅者
    //定义与点云相关的一系列的发布者
    ros::Publisher pubFullCloud;
    ros::Publisher pubFullInfoCloud;

    ros::Publisher pubGroundCloud;
    ros::Publisher pubSegmentedCloud;
    ros::Publisher pubSegmentedCloudPure;
    ros::Publisher pubSegmentedCloudInfo;
    ros::Publisher pubOutlierCloud;

//定义一系列的点云存储
    pcl::PointCloud<PointType>::Ptr laserCloudIn;//雷达传出的点云(以指针代表它)
    //typedef pcl::PointXYZI  PointType;已经在utility.h中定义好了
    pcl::PointCloud<PointType>::Ptr fullCloud;//全部点云
    pcl::PointCloud<PointType>::Ptr fullInfoCloud;//整体点云

    pcl::PointCloud<PointType>::Ptr groundCloud;//地面点云
    pcl::PointCloud<PointType>::Ptr segmentedCloud;//分割后的点云
    pcl::PointCloud<PointType>::Ptr segmentedCloudPure;//分割后的几何信息
    pcl::PointCloud<PointType>::Ptr outlierCloud;//异常点云

    PointType nanPoint;

    cv::Mat rangeMat;//一个点云投影后的range image矩阵
    cv::Mat labelMat;//一个点云投影后的标签矩阵
    cv::Mat groundMat;//一个点云投影后的地面矩阵
    int labelCount;

    float startOrientation;//一帧点云的起始角和结束角
    float endOrientation;

    cloud_msgs::cloud_info segMsg;//在src文件夹并列的msg文件夹中单独定义的
    std_msgs::Header cloudHeader;//Header有3个成员,uint32 seq; time stamp; string frame_id

    std::vector<std::pair<uint8_t, uint8_t> > neighborIterator;

    uint16_t *allPushedIndX;
    uint16_t *allPushedIndY;

    uint16_t *queueIndX;
    uint16_t *queueIndY;

public:
    ImageProjection():
        nh("~"){
        // 订阅来自velodyne雷达驱动的topic ("/velodyne_points")
        /*
         例子ros::Subscriber sub = n.subscribe("chatter", 1000, &Listener::callback, &listener);
         使用类内函数时,将第4个参数替换成this:
         ros::Subscriber sub = n.subscribe("chatter", 1000, &类名::函数名, this);
        */
        subLaserCloud = nh.subscribe<sensor_msgs::PointCloud2>("/velodyne_points", 1, &ImageProjection::cloudHandler, this);
        
        pubFullCloud = nh.advertise<sensor_msgs::PointCloud2> ("/full_cloud_projected", 1);
        pubFullInfoCloud = nh.advertise<sensor_msgs::PointCloud2> ("/full_cloud_info", 1);

        pubGroundCloud = nh.advertise<sensor_msgs::PointCloud2> ("/ground_cloud", 1);
        pubSegmentedCloud = nh.advertise<sensor_msgs::PointCloud2> ("/segmented_cloud", 1);
        pubSegmentedCloudPure = nh.advertise<sensor_msgs::PointCloud2> ("/segmented_cloud_pure", 1);
        pubSegmentedCloudInfo = nh.advertise<cloud_msgs::cloud_info> ("/segmented_cloud_info", 1);
        pubOutlierCloud = nh.advertise<sensor_msgs::PointCloud2> ("/outlier_cloud", 1);

        nanPoint.x = std::numeric_limits<float>::quiet_NaN();
        nanPoint.y = std::numeric_limits<float>::quiet_NaN();
        nanPoint.z = std::numeric_limits<float>::quiet_NaN();
        nanPoint.intensity = -1;

        allocateMemory();//申请资源源码中在构造函数申请了资源，有些是智能指针，会自动释放资源，
        //但是另外有4个数组不会，会产生资源泄露。最好在析构函数中进行资源释放。
        resetParameters();//初始化
    }

	// 初始化各类参数以及分配内存(涉及到内存分配的问题)
    void allocateMemory(){

        laserCloudIn.reset(new pcl::PointCloud<PointType>());

        fullCloud.reset(new pcl::PointCloud<PointType>());
        fullInfoCloud.reset(new pcl::PointCloud<PointType>());

        groundCloud.reset(new pcl::PointCloud<PointType>());
        segmentedCloud.reset(new pcl::PointCloud<PointType>());
        segmentedCloudPure.reset(new pcl::PointCloud<PointType>());
        outlierCloud.reset(new pcl::PointCloud<PointType>());

        fullCloud->points.resize(N_SCAN*Horizon_SCAN);
        fullInfoCloud->points.resize(N_SCAN*Horizon_SCAN);

        segMsg.startRingIndex.assign(N_SCAN, 0);
        segMsg.endRingIndex.assign(N_SCAN, 0);

        segMsg.segmentedCloudGroundFlag.assign(N_SCAN*Horizon_SCAN, false);
        segMsg.segmentedCloudColInd.assign(N_SCAN*Horizon_SCAN, 0);
        segMsg.segmentedCloudRange.assign(N_SCAN*Horizon_SCAN, 0);

		// labelComponents函数中用到了这个矩阵
		// 该矩阵用于求某个点的上下左右4个邻接点
        std::pair<int8_t, int8_t> neighbor;
        neighbor.first = -1; neighbor.second =  0; neighborIterator.push_back(neighbor);
        neighbor.first =  0; neighbor.second =  1; neighborIterator.push_back(neighbor);
        neighbor.first =  0; neighbor.second = -1; neighborIterator.push_back(neighbor);
        neighbor.first =  1; neighbor.second =  0; neighborIterator.push_back(neighbor);

        allPushedIndX = new uint16_t[N_SCAN*Horizon_SCAN];
        allPushedIndY = new uint16_t[N_SCAN*Horizon_SCAN];

        queueIndX = new uint16_t[N_SCAN*Horizon_SCAN];
        queueIndY = new uint16_t[N_SCAN*Horizon_SCAN];
    }

    // 下面的reset函数在回调函数中每次都要调用一次,与allocateMemory函数不同,reset函数只是清空数据,不涉及内存分配
    void resetParameters(){
        laserCloudIn->clear();
        groundCloud->clear();
        segmentedCloud->clear();
        segmentedCloudPure->clear();
        outlierCloud->clear();

        rangeMat = cv::Mat(N_SCAN, Horizon_SCAN, CV_32F, cv::Scalar::all(FLT_MAX));
        //OpenCV里的Scalar::all(0),意思是所有元素设置为0;CV_8S和CV_32F是数据类型
        groundMat = cv::Mat(N_SCAN, Horizon_SCAN, CV_8S, cv::Scalar::all(0));
        labelMat = cv::Mat(N_SCAN, Horizon_SCAN, CV_32S, cv::Scalar::all(0));
        labelCount = 1;

        std::fill(fullCloud->points.begin(), fullCloud->points.end(), nanPoint);
        std::fill(fullInfoCloud->points.begin(), fullInfoCloud->points.end(), nanPoint);
    }

    ~ImageProjection(){}
	//析构函数是构造函数的反面,为了释放对象的内存空间;但正常时,构造函数都默认有这个析构函数,但为什么还需新加,原因未知?
   
    //点云的回调函数
    void cloudHandler(const sensor_msgs::PointCloud2ConstPtr& laserCloudMsg){
        //每接受到一帧新的点云信息时,都会进入到回调函数中,主要是调用函数的接口即可
        copyPointCloud(laserCloudMsg);//点云的复制函数:将点云格式转换为PCL格式
        findStartEndAngle();//扫描的开始和结束角度:找到点云的起始和终止角
        projectPointCloud();//点云投影函数:点云重投影到Rang Image

        //下面是相对于LOAM改进的
        groundRemoval();//地面检测函数:提取地面点
        cloudSegmentation();//点云分割函数:得到分割点云，就是聚类
        publishCloud();//点云发布函数:发布分隔点云
        resetParameters();//为下一次迭代重置参数:清除该帧的点云信息
    }
//将起始点和最末点进行角度转换函数

    void copyPointCloud(const sensor_msgs::PointCloud2ConstPtr& laserCloudMsg){
        cloudHeader = laserCloudMsg->header;//获取该帧点云的时间戳
        pcl::fromROSMsg(*laserCloudMsg, *laserCloudIn);//后者将数据给了前者
        // 将ROS中的sensor_msgs::PointCloud2ConstPtr类型转换到pcl点云库指针
        //两种情形下需要进行数据类型转换
    }
    void findStartEndAngle(){
        // 雷达坐标系：右->X,前->Y,上->Z 雷达内部旋转扫描方向：Z轴俯视下来，顺时针方向（Z轴右手定则反向）
        // atan2(y,x)函数的返回值范围(-PI,PI],表示与复数x+yi的幅角
        // segMsg.startOrientation范围为(-PI,PI] ,segMsg.endOrientation范围为(PI,3PI]
        // 因为内部雷达旋转方向原因，所以atan2(..)函数前面需要加一个负号
        segMsg.startOrientation = -atan2(laserCloudIn->points[0].y, laserCloudIn->points[0].x);
        // 下面这句话怀疑作者可能写错了，laserCloudIn->points.size() - 2应该是laserCloudIn->points.size() - 1
segMsg.endOrientation = -atan2(laserCloudIn->points[laserCloudIn->points.size() - 1].y, laserCloudIn->points[laserCloudIn->points.size() - 2].x) + 2 * M_PI;
		// 开始和结束的角度差一般是多少？
		// 一个velodyne 雷达数据包转过的角度多大？
        // 雷达一般包含的是一圈的数据，所以角度差一般是2*PI，一个数据包转过360度

		// segMsg.endOrientation - segMsg.startOrientation范围为(0,4PI)
        // 如果角度差大于3Pi或小于Pi，说明角度差有问题，进行调整。
        if (segMsg.endOrientation - segMsg.startOrientation > 3 * M_PI) {
            segMsg.endOrientation -= 2 * M_PI;
        } else if (segMsg.endOrientation - segMsg.startOrientation < M_PI)
            segMsg.endOrientation += 2 * M_PI;
		// segMsg.orientationDiff的范围为(PI,3PI),一圈大小为2PI，应该在2PI左右
        segMsg.orientationDiff = segMsg.endOrientation - segMsg.startOrientation;
    }
    //下面这一步是将点云投影到RangeImage里面,原始点云是一个球形,我们把它展开成一个图片.
    //以16线激光为例，转换的range图，长为16，宽为旋转一周的采样次数，这里为1800，因此最后得到的是16*1800的图像!!!关键过度句!
    void projectPointCloud(){
        //逐一计算点云深度,并具有深度的点云保存在fullInfoCloud中
        float verticalAngle, horizonAngle, range;
        size_t rowIdn, columnIdn, index, cloudSize; 
        PointType thisPoint;

        cloudSize = laserCloudIn->points.size();

        for (size_t i = 0; i < cloudSize; ++i){

            thisPoint.x = laserCloudIn->points[i].x;
            thisPoint.y = laserCloudIn->points[i].y;
            thisPoint.z = laserCloudIn->points[i].z;

            // 计算竖直方向上的角度（雷达的第几线）
            verticalAngle = atan2(thisPoint.z, sqrt(thisPoint.x * thisPoint.x + thisPoint.y * thisPoint.y)) * 180 / M_PI;
			
            // rowIdn计算出该点激光雷达是竖直方向上第几线的
			// 从下往上计数，-15度记为初始线，第0线，一共16线(N_SCAN=16)
            rowIdn = (verticalAngle + ang_bottom) / ang_res_y;//求出Rang Image中行号对应激光雷达线束的行号(此数值大于0)
            if (rowIdn < 0 || rowIdn >= N_SCAN)
                continue;

            // atan2(y,x)函数的返回值范围(-PI,PI],表示与复数x+yi的幅角
            // 下方角度atan2(..)交换了x和y的位置，计算的是与y轴正方向的夹角大小(关于y=x做对称变换)
            // 这里是在雷达坐标系，所以是与正前方的夹角大小
            horizonAngle = atan2(thisPoint.x, thisPoint.y) * 180 / M_PI;

			// round函数进行四舍五入取整
			// 这边确定不是减去180度???  不是
			// 雷达水平方向上某个角度和水平第几线的关联关系???关系如下：
			// horizonAngle:(-PI,PI],columnIdn:[H/4,5H/4]-->[0,H] (H:Horizon_SCAN)
			// 下面是把坐标系绕z轴旋转,对columnIdn进行线性变换
			// x+==>Horizon_SCAN/2,x-==>Horizon_SCAN
			// y+==>Horizon_SCAN*3/4,y-==>Horizon_SCAN*5/4,Horizon_SCAN/4
            //
            //          3/4*H
            //          | y+
            //          |
            // (x-)H---------->H/2 (x+)
            //          |
            //          | y-
            //    5/4*H   H/4
            //
            columnIdn = -round((horizonAngle-90.0)/ang_res_x) + Horizon_SCAN/2;
            if (columnIdn >= Horizon_SCAN)
                columnIdn -= Horizon_SCAN;
            // 经过上面columnIdn -= Horizon_SCAN的变换后的columnIdn分布：
            //          3/4*H
            //          | y+
            //     H    |
            // (x-)---------->H/2 (x+)
            //     0    |
            //          | y-
            //         H/4
            //
            if (columnIdn < 0 || columnIdn >= Horizon_SCAN)
                continue;

            range = sqrt(thisPoint.x * thisPoint.x + thisPoint.y * thisPoint.y + thisPoint.z * thisPoint.z);
            //上面的作用是Range Image中存储点云的深度信息
            rangeMat.at<float>(rowIdn, columnIdn) = range;

			// columnIdn:[0,H] (H:Horizon_SCAN)==>[0,1800]
            thisPoint.intensity = (float)rowIdn + (float)columnIdn / 10000.0;

            index = columnIdn  + rowIdn * Horizon_SCAN;
            fullCloud->points[index] = thisPoint;
            //将点云信息存入fullCloud和fullInfoCloud，两者的区别在于
            //第一个中的强度信息填入了行号和列号相关的信息，而后者填入的是深度信息.
            fullInfoCloud->points[index].intensity = range;
        }
    }
    void groundRemoval(){
//利用不同的扫描圈来表示地面.进而检测地面是否水平.例如在源码中的7个扫描圈,每两个圈之间进行一次比较,
//角度相差10度以内,我们可以看作做是平地.并且将扫描圈中的点加入到groundCloud点云中
        size_t lowerInd, upperInd;
        float diffX, diffY, diffZ, angle;

        for (size_t j = 0; j < Horizon_SCAN; ++j){
            // groundScanInd 是在 utility.h 文件中声明的线数，groundScanInd=7
            for (size_t i = 0; i < groundScanInd; ++i){

                lowerInd = j + ( i )*Horizon_SCAN;
                upperInd = j + (i+1)*Horizon_SCAN;

                // 初始化的时候用nanPoint.intensity = -1 填充
                // 都是-1 证明是空点nanPoint
                if (fullCloud->points[lowerInd].intensity == -1 ||
                    fullCloud->points[upperInd].intensity == -1){
                    groundMat.at<int8_t>(i,j) = -1;//-1时候代表无法判断是否为地面点
                    continue;
                }
				// 由上下两线之间点的XYZ位置得到两线之间的俯仰角
				// 如果俯仰角在10度以内，则判定(i,j)为地面点,并标记结果记在cv::Mat::groundMat里面,令groundMat[i][j]=1
				// 否则，则不是地面点，则进行点云分割,否则不进行点云分割
                diffX = fullCloud->points[upperInd].x - fullCloud->points[lowerInd].x;
                diffY = fullCloud->points[upperInd].y - fullCloud->points[lowerInd].y;
                diffZ = fullCloud->points[upperInd].z - fullCloud->points[lowerInd].z;

                angle = atan2(diffZ, sqrt(diffX*diffX + diffY*diffY) ) * 180 / M_PI;

                if (abs(angle - sensorMountAngle) <= 10){
                    groundMat.at<int8_t>(i,j) = 1;//1代表是地面点
                    groundMat.at<int8_t>(i+1,j) = 1;
                }
            }
        }
		// 找到所有点中的地面点或者距离为FLT_MAX(rangeMat的初始值)的点，并将他们标记为-1
		// extract ground cloud (groundMat == 1)
        // mark entry that doesn't need to label (ground and invalid point) for segmentation
        // note that ground remove is from 0~N_SCAN-1, need rangeMat for mark label matrix for the 16th scan
        for (size_t i = 0; i < N_SCAN; ++i){
            for (size_t j = 0; j < Horizon_SCAN; ++j){
                if (groundMat.at<int8_t>(i,j) == 1 || rangeMat.at<float>(i,j) == FLT_MAX){//FLT_MAX为初始化值
                    labelMat.at<int>(i,j) = -1;//单通道图像的使用办法:image.at<uchar>(i,j) = 255
                    //Mat类中的at方法作用：用于获取图像矩阵某点的值或改变某点的值
                }
            }
        }
		// 如果有节点订阅groundCloud，那么就需要把地面点发布出来;具体实现过程：把点放到groundCloud队列中去
        if (pubGroundCloud.getNumSubscribers() != 0){
            for (size_t i = 0; i <= groundScanInd; ++i){
                for (size_t j = 0; j < Horizon_SCAN; ++j){
                    if (groundMat.at<int8_t>(i,j) == 1)
                        groundCloud->push_back(fullCloud->points[j + i*Horizon_SCAN]);
                }
            }
        }
    }
    void cloudSegmentation(){
       //上面函数是将点云分为地面点与可被分配的四周被扫描的点,将其筛选后分别纳入被分割的点云
           //下面for循环是在排除地面点与异常点后,逐一检测邻点特征并生成局部特征
        for (size_t i = 0; i < N_SCAN; ++i)
            for (size_t j = 0; j < Horizon_SCAN; ++j)
				// 如果labelMat[i][j]=0,表示没有对该点进行过分类
				// 需要对该点进行聚类
                if (labelMat.at<int>(i,j) == 0)
                    labelComponents(i, j);//核心函数
        int sizeOfSegCloud = 0;
        for (size_t i = 0; i < N_SCAN; ++i) {
			// segMsg.startRingIndex[i]
			// segMsg.endRingIndex[i]
			// 表示第i线的点云起始序列和终止序列
			// 以开始线后的第6线为开始，以结束线前的第6线为结束
            segMsg.startRingIndex[i] = sizeOfSegCloud-1 + 5;

            for (size_t j = 0; j < Horizon_SCAN; ++j) {
				// 找到可用的特征点或者地面点(不选择labelMat[i][j]=0的点)
                    //如果被认可的特征点或者是地面点,就可以纳入到被分割的点云
                if (labelMat.at<int>(i,j) > 0 || groundMat.at<int8_t>(i,j) == 1){
					// labelMat数值为999999表示这个点是因为聚类数量不够30而被舍弃的点
					// 需要舍弃的点直接continue跳过本次循环，
					// 当列数为5的倍数，并且行数较大，可以认为非地面点的，将它保存进异常点云(界外点云)中
					// 然后再跳过本次循环
                    //离群点或异常点的处理
                    if (labelMat.at<int>(i,j) == 999999){
                        //当等于999999时候,代表labelMat是舍弃点
                        if (i > groundScanInd && j % 5 == 0){
                            outlierCloud->push_back(fullCloud->points[j + i*Horizon_SCAN]);
                            continue;
                        }else{
                            continue;
                        }
                    }
					// 如果是地面点,对于列数不为5的倍数的，直接跳过不处理
                    if (groundMat.at<int8_t>(i,j) == 1){
                        if (j%5!=0 && j>5 && j<Horizon_SCAN-5)
                            continue;
                    }
					// 上面多个if语句已经去掉了不符合条件的点，这部分直接进行信息的拷贝和保存操作
					// 保存完毕后sizeOfSegCloud递增
                    segMsg.segmentedCloudGroundFlag[sizeOfSegCloud] = (groundMat.at<int8_t>(i,j) == 1);
                    segMsg.segmentedCloudColInd[sizeOfSegCloud] = j;
                    segMsg.segmentedCloudRange[sizeOfSegCloud]  = rangeMat.at<float>(i,j);
                    segmentedCloud->push_back(fullCloud->points[j + i*Horizon_SCAN]);
                    ++sizeOfSegCloud;
                }
            }
            // 以结束线前的第5线为结束
            segMsg.endRingIndex[i] = sizeOfSegCloud-1 - 5;
        }
		// 如果有节点订阅SegmentedCloudPure,(分割后的几何信息)
		// 那么把点云数据保存到segmentedCloudPure中去
        if (pubSegmentedCloudPure.getNumSubscribers() != 0){
            for (size_t i = 0; i < N_SCAN; ++i){
                for (size_t j = 0; j < Horizon_SCAN; ++j){
					// 需要选择不是地面点(labelMat[i][j]!=-1)和没被舍弃的点
                    if (labelMat.at<int>(i,j) > 0 && labelMat.at<int>(i,j) != 999999){
                        segmentedCloudPure->push_back(fullCloud->points[j + i*Horizon_SCAN]);
                        segmentedCloudPure->points.back().intensity = labelMat.at<int>(i,j);
                    }
                }
            }
        }
    }
    void labelComponents(int row, int col){
        //该部分是点云分割部分,点云分为很多的簇,来自同一簇的点被分配唯一一个的标签
        //此函数对点云进行标记.通过标准的BFS算法对点进行标记:以(row,col)为中心向外面扩散,判断(row,col)是否属于平面中的一点
        //该函数对特征的检测进行了详细的描述,并且是针对某一特定的点与其邻点的计算过程
        float d1, d2, alpha, angle;
        int fromIndX, fromIndY, thisIndX, thisIndY; 
        bool lineCountFlag[N_SCAN] = {false};

        queueIndX[0] = row;
        queueIndY[0] = col;
        int queueSize = 1;
        int queueStartInd = 0;
        int queueEndInd = 1;

        allPushedIndX[0] = row;
        allPushedIndY[0] = col;
        int allPushedIndSize = 1;
        // BFS(breadth广度)算法作用是以(row，col)为中心向外面扩散，判断(row,col)是否是这个平面中一点
        while(queueSize > 0){
            fromIndX = queueIndX[queueStartInd];
            fromIndY = queueIndY[queueStartInd];
            --queueSize;
            ++queueStartInd;
			// labelCount的初始值为1，后面会递增
            labelMat.at<int>(fromIndX, fromIndY) = labelCount;
			// neighbor=[[-1,0];[0,1];[0,-1];[1,0]]
			// 遍历点[fromIndX,fromIndY]边上的四个邻点
            for (auto iter = neighborIterator.begin(); iter != neighborIterator.end(); ++iter){

                thisIndX = fromIndX + (*iter).first;
                thisIndY = fromIndY + (*iter).second;

                if (thisIndX < 0 || thisIndX >= N_SCAN)
                    continue;
                // 是个环状的图片，左右连通
                if (thisIndY < 0)
                    thisIndY = Horizon_SCAN - 1;
                if (thisIndY >= Horizon_SCAN)
                    thisIndY = 0;
				// 如果点[thisIndX,thisIndY]已经标记过
				// labelMat中，-1代表地面点，0代表未进行标记过，999999为无效点,其余为其他的标记,同一个数值代表同一个聚类
				// 如果当前的邻点已经标记过，则跳过该点。
				// 如果labelMat已经标记为正整数，则已经聚类完成，不需要再次对该点聚类
                if (labelMat.at<int>(thisIndX, thisIndY) != 0)
                    continue;

                d1 = std::max(rangeMat.at<float>(fromIndX, fromIndY), 
                              rangeMat.at<float>(thisIndX, thisIndY));
                d2 = std::min(rangeMat.at<float>(fromIndX, fromIndY), 
                              rangeMat.at<float>(thisIndX, thisIndY));

				// alpha代表角度分辨率，
				// X方向上角度分辨率是segmentAlphaX(rad)
				// Y方向上角度分辨率是segmentAlphaY(rad)
                if ((*iter).first == 0)
                    alpha = segmentAlphaX;
                else
                    alpha = segmentAlphaY;
				/*通过下面的公式计算这两点之间是否有平面特征*/
				// atan2(y,x)的值越大，d1，d2之间的差距越小,证明是同一类的点,如果差距较大就证明不是同一类的点
                angle = atan2(d2*sin(alpha), (d1 -d2*cos(alpha)));

                if (angle > segmentTheta){
					// segmentTheta=1.0472<==>60度 ,如果算出角度大于60度，则假设这是同一类的点云
                    queueIndX[queueEndInd] = thisIndX;
                    queueIndY[queueEndInd] = thisIndY;
                    ++queueSize;
                    ++queueEndInd;

                    labelMat.at<int>(thisIndX, thisIndY) = labelCount;
                    lineCountFlag[thisIndX] = true;

                    allPushedIndX[allPushedIndSize] = thisIndX;
                    allPushedIndY[allPushedIndSize] = thisIndY;
                    ++allPushedIndSize;
                }
            }
        }
        bool feasibleSegment = false;
		// 如果聚类超过30个点，直接标记为一个可用聚类，labelCount需要递增分成为不同的聚类
        if (allPushedIndSize >= 30)
            feasibleSegment = true;
        else if (allPushedIndSize >= segmentValidPointNum){
			// 如果聚类点数小于30大于等于5，统计竖直方向上的聚类点数.
            int lineCount = 0;
            for (size_t i = 0; i < N_SCAN; ++i)
                if (lineCountFlag[i] == true)
                    ++lineCount;
			// 竖直方向上超过3个也将它标记为有效聚类
            if (lineCount >= segmentValidLineNum)
                feasibleSegment = true;            
        }
        if (feasibleSegment == true){
            ++labelCount;
        }else{
            for (size_t i = 0; i < allPushedIndSize; ++i){
				// 标记为999999的是需要舍弃聚类的点，因为他们的数量小于30个
                labelMat.at<int>(allPushedIndX[i], allPushedIndY[i]) = 999999;
            }
        }
    }
    // 发布各类点云内容
    void publishCloud(){
        //在我们计算的过程中参考系均为机器人自身参考系,frame_id自然是base_link
    	// 发布cloud_msgs::cloud_info消息
        segMsg.header = cloudHeader;//header里包含3个成员,uint32 seq; time stamp; string frame_id
        pubSegmentedCloudInfo.publish(segMsg);

        sensor_msgs::PointCloud2 laserCloudTemp;//定义了一类点云数据结构

		// pubOutlierCloud发布无效的界外点云
        pcl::toROSMsg(*outlierCloud, laserCloudTemp);//前者将数据给了后者与fromROSMsg相反
        laserCloudTemp.header.stamp = cloudHeader.stamp;
        laserCloudTemp.header.frame_id = "base_link";
        //将上述三个语法步骤中的数据存储在laserCloundTemp里面,然后进行发布
        pubOutlierCloud.publish(laserCloudTemp);

		// pubSegmentedCloud发布分割后的点云
        pcl::toROSMsg(*segmentedCloud, laserCloudTemp);
        laserCloudTemp.header.stamp = cloudHeader.stamp;
        laserCloudTemp.header.frame_id = "base_link";
        pubSegmentedCloud.publish(laserCloudTemp);

        //发布全部点云(不带range信息的)
        if (pubFullCloud.getNumSubscribers() != 0){
            pcl::toROSMsg(*fullCloud, laserCloudTemp);
            laserCloudTemp.header.stamp = cloudHeader.stamp;
            laserCloudTemp.header.frame_id = "base_link";
            pubFullCloud.publish(laserCloudTemp);
        }
        //发布地面点云信息
        if (pubGroundCloud.getNumSubscribers() != 0){
            pcl::toROSMsg(*groundCloud, laserCloudTemp);
            laserCloudTemp.header.stamp = cloudHeader.stamp;
            laserCloudTemp.header.frame_id = "base_link";//与此数据相关联的帧
            pubGroundCloud.publish(laserCloudTemp);
        }
         //发布分割后点云的几何信息
        if (pubSegmentedCloudPure.getNumSubscribers() != 0){
            pcl::toROSMsg(*segmentedCloudPure, laserCloudTemp);
            laserCloudTemp.header.stamp = cloudHeader.stamp;
            laserCloudTemp.header.frame_id = "base_link";
            pubSegmentedCloudPure.publish(laserCloudTemp);
        }
        //发布带range深度信息的点云
        if (pubFullInfoCloud.getNumSubscribers() != 0){
            pcl::toROSMsg(*fullInfoCloud, laserCloudTemp);
            laserCloudTemp.header.stamp = cloudHeader.stamp;
            laserCloudTemp.header.frame_id = "base_link";
            pubFullInfoCloud.publish(laserCloudTemp);
        }
    }
};
int main(int argc, char** argv){

    ros::init(argc, argv, "lego_loam");
    
    ImageProjection IP;//定义自定义类ImageProjection的对象?什么作用

    ROS_INFO("\033[1;32m---->\033[0m Image Projection Started.");

    ros::spin();//所有节点都要加入此函数,为处理节点订阅话题的所有回调函数
    return 0;
}
