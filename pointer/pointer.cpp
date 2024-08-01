#include <stdio.h>
#include <iostream>
int main(int argc, char const *argv[])
{
    // int* x=0;
    // *x=100;
    // printf("*x= %d",*x);
    int a=10;
    // int *thisImu = &a; //如此声明的指针是不是内存泄漏
    int *thisImu=new int();
    *thisImu=a;
    std::cout<<"*thisImu= "<<*thisImu<<std::endl;
    printf("jsjdasdojo");
    return 0;
}
