#include <iostream>
    class Point
    {
    private:
        int x,y;
    public:
        void process()
        {
            std::cout<<this->x<<std::endl;
            std::cout<<y<<std::endl;
            y++;
        }
        Point(/* args */);
        ~Point();
    };
//下面是C语言的伪码
/*struct Point
{
    int x;
    int y;
};
void process(Point* this)
{
    std::cout<<this->x<<std::endl;
    std::cout<<this->y<<std::endl;
    this->y++;
}*/

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
