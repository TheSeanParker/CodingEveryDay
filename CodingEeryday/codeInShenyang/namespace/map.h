#include <iostream>
namespace cslam
{
    class viewer;
    class map
    {
    private:
        /* data */
        int abc;
    public:
        map(/* args */);
        ~map();
    };
    
    map::map(/* args */)
    {
        std::cout<<"zaici进入到map类里"<<std::endl;
    }
    
    map::~map()
    {
    }
    
} // namespace cslam
