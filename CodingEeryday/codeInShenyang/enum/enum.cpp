#include <iostream>

int main(int argc, char const *argv[])
{
    /* code */
        enum eTrackingState
    {
        SYSTEM_NOT_READY =100,
        NO_IMAGES_YET ,
        NOT_INITIALIZED ,
        OK,
        RECENTLY_LOST,
        LOST ,
        OK_KLT
    };
    eTrackingState state;
    state=LOST;
    if (state == LOST)
    {
        std::cout<<"output="<<state<<std::endl;
    }
    
    return 0;
}
