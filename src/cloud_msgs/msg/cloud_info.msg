Header header 

int32[] startRingIndex #分割的起始和结束的索引 长度：N_SCAN
int32[] endRingIndex

float32 startOrientation #分割的起始和结束的角度和差值
float32 endOrientation
float32 orientationDiff

bool[]    segmentedCloudGroundFlag # true - ground point, false - other points
uint32[]  segmentedCloudColInd   # point column index in range image
float32[] segmentedCloudRange  # point range 



