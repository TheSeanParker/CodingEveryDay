
#include "map.h"
namespace cslam
{
    class viewer
    {
    private:
        /* data */
        int a;
    public:
        viewer(/* args */);
        ~viewer();
    };
    
    viewer::viewer(/* args */)
    {
        std::cout<<"输出数据viewer"<<std::endl;
    }
    
    viewer::~viewer()
    {
    }
    class map;
} // namespace cslam

int main(int argc, char const *argv[])
{
    /* code */
    cslam::viewer v;
    cslam::map m;
    std::cout<<"输出数据"<<std::endl;
    return 0;
}
