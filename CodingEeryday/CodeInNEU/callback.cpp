#include <cstdio>
int sub(int a, int b)
{
    return a+b;
}
//下面叫做中间函数
int test(int(* p)(int,int),int a,int b)
{//(*p)必须加括号需要思考一下，定义一个名为p的函数指针，p指向的函数要求有两个int输入参数
    return (*p)(a,b);
}
int main(int argc, char const *argv[])
{
    /* code */
    int hou=19;
    int dian=92;
    int temp=test(sub,hou,dian);
    printf("%d\n",temp);
    return 0;
}
