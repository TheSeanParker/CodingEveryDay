
class Point
{
    int x;
};
int main(int argc, char const *argv[])
{
    /* code */
    Point *p1=new Point();
    Point *p2=new Point();
    Point p3;
    Point p4;
    p3=p4;   //栈->栈
    p3=*p1;  //栈->堆
    *p1=p3;  //堆->栈
    *p2=*p2; //堆->堆
    return 0;
}
