    #include <iostream>
    using namespace std;
    class A
    {
    public:
        virtual void Print() { cout << "A::Print" << endl; }
    };
    class B : public A
    {
    public:
        virtual void Print() { cout << "B::Print" << endl; }
    };
    class D : public A
    {
    public:
        virtual void Print() { cout << "D::Print" << endl; }
    };
    class E : public B
    {
        virtual void Print() { cout << "E::Print" << endl; }
    };
    int main()
    {
        A  a; B b; D d; E e;
        A *pa =new A(); 
        B *pb = &b;
        pa->Print();    //多态， a.Print()被调用，输出：A::Print
        pa = pb;        //基类指针pa指向派生类对象b
        pa->Print();  //b.Print()被调用，输出：B::Print
        pa = &d;       //基类指针pa指向派生类对象d
        pa->Print();  //多态， d. Print ()被调用,输出：D::Print
        pa = &e;       //基类指针pa指向派生类对象d
        pa->Print();  //多态， e.Print () 被调用,输出：E::Print
        return 0;
    }