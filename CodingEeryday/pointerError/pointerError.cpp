#include<iostream>
//要想把下面的理顺清楚，就一定要进行整理好对应的【内存所有权】
    int* glob;
    void process(int* q)
    {
        glob=q;//传递所有权，不推荐这样写
    }
        void g1()
        {
            int *p=new int{7};
            process(p);
            delete p;//将此处指向的对象，进行删除
            std::cout<<"*glob的数值="<<*glob<<std::endl;
            //..
            *glob=9;//解引用一个不存在指向的指针，悬浮指针：所有权不属于自己，但是硬要往里面写东西
            
        }
    void g2()
    {
        int* p=new int{8};
        process(p);
        delete p;
        std::cout<<"*glob的数值="<<*glob<<std::endl;
          //..
        delete glob;//重复删除
    }
        void g3()
        {
            int x=3;
            int* p=&x;
            process(p);
            delete glob;//内存泄漏？答：删除的是栈对象，delete只是删除堆对象
        
        }
    int main(int argc, char const *argv[])
    {
        /* code */
        g1();
        g2();
        g3();
            // int x=3;
            // int *p=&x;
            // std::cout<<"*p first的数值="<<*p<<std::endl;
            // *p=33;
            // std::cout<<"*p second的数值="<<*p<<std::endl;
        return 0;
    }
