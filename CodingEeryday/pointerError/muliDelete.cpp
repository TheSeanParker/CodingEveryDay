#include<iostream>
//要想把下面的理顺清楚，就一定要进行整理好对应的【内存所有权】
    int* glob;
    void process(int* q)
    {
        glob=q;//传递所有权，不推荐这样写
    }
    void g2()
    {
        int* p=new int{8};
        process(p);
        std::cout<<"delete前glob的数值="<<glob<<std::endl;
        std::cout<<"delete前*glob的数值="<<*glob<<std::endl;//*glob=8
        delete p;
        std::cout<<"delete后p的数值="<<p<<std::endl;//p=0？！delete之后，p的数值是不变的，指向对象是置空的
        std::cout<<"delete后*p的数值="<<*p<<std::endl;//0
        std::cout<<"delete后glob的数值="<<glob<<std::endl;//glob=前
        std::cout<<"*glob的数值="<<*glob<<std::endl;//0
        //..
        //delete glob;//重复删除,如果换成了其他的对象，那么将会将使用这块内存的进行释放是错误的
        //其次，如果glob的类型是类类型，将会导致函数在后续引发一系列的问题
    }
       
    int main(int argc, char const *argv[])
    {
        /* code */
        g2();
            // int x=3;
            // int *p=&x;
            // std::cout<<"*p first的数值="<<*p<<std::endl;
            // *p=33;
            // std::cout<<"*p second的数值="<<*p<<std::endl;
        return 0;
    }
