//43 min
int* glob;

void process(int* q)
{
    glob=q;
}
void g1()
{
    int* p=new int{7};
    process(p);
    delete p;
    *glob=9;
}
int main(int argc, char const *argv[])
{
    g1();
    return 0;
}
