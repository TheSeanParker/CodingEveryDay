#include <iostream>
union   
{ 
	float   fuel_load; 
	char a[3];
          // char b[9];
	int   pallets; 
}fighter; 

struct   aircraft 
{ 
          int   wingspan; //4
          int   passengers; //4
          union   
          { 
                    float   fuel_load; //4
                    float   bomb_load; //4
                    long   pallets; //4
          }; 
}test2; 

union   
{ 
          struct 
          {
             float   fuel_load; //4
          //    float   bomb_load; //4
          //    float   pallets; //4
          };
          float data[4];
}test3; 

// PCL中的PointXYZ数据类型
union
{
  float data[4];
  struct
  {
    float x;
    float y;
    float z;
    char d;
    bool e;
  };
}PointXYZ;
int main(int argc, char const *argv[])
{
          /* code */
          std::cout<<"size="<<sizeof(fighter)<<std::endl;
          std::cout<<"test2="<<sizeof(test2)<<std::endl;
          std::cout<<"test3="<<sizeof(test3)<<std::endl;
	 std::cout<<"PointXYZ="<<sizeof(PointXYZ)<<std::endl;
          return 0;
}
