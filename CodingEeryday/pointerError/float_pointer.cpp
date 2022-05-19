#include<iostream>
//要想把下面的理顺清楚，就一定要进行整理好对应的【内存所有权】
//探讨delete的本质，了解delete的目的是为了，将此块地址对应的对象链接关系取消掉，对应地址依然保留着
    int* glob;

    void process(int* q)
    {
        glob=q;//传递所有权，不推荐这样写
    }
        void g1()
        {
            int *p=new int{7};
                    std::cout<<"p的初始指针数值="<<p<<std::endl;//一个地址
            process(p);
                    std::cout<<"delete p前 *p的指针数值="<<*p<<std::endl;
                    std::cout<<"glob的初始指针数值="<<glob<<std::endl;//与p相等
            delete p;//将此处指向的对象，进行删除
                    std::cout<<"delete p后 p的指针数值="<<p<<std::endl;//p=0？
                    std::cout<<"delete p后 *p的指针数值="<<*p<<std::endl;//*p=0
                    std::cout<<"glob此后指针数值="<<glob<<std::endl;//glob不变
                    std::cout<<"*glob此后指针数值="<<*glob<<std::endl;///*重点*/解引用的值是0；
            *glob=9;//解引用一个不存在指向的指针，悬浮指针：所有权不属于自己，但硬往里写东西
                    //当这块内存没有被使用时候，也没有什么。但是这块内存分配给别人时
                    //硬往里写就会导致，这块内存对应的数值被改变且不容易发现
        }
    int main(int argc, char const *argv[])
    {
        /* code */
        std::cout<<"glob的初始指针数值="<<glob<<std::endl;
        g1();
            // int x=3;
            // int *p=&x;
            // std::cout<<"*p first的数值="<<*p<<std::endl;
            // *p=33;
            // std::cout<<"*p second的数值="<<*p<<std::endl;
        return 0;
    }
