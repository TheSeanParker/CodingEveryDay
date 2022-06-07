#include <iostream>
//在类内private的地方进行定义变量，
//在类的构造函数里面进行初始化变量
    class Queue
    {
        enum{Q_SIZE=10};//思考为什么打开括号就是不行的？
        //static const int Q_SIZE=10;
        //上下两种方式都是为了在类内部声明一个常量值，但是作用阈是不同的
    private:
        struct Node
        {
            int item;
            struct Node* next;};
        Node* front;
        Node* rear;
        int items;
        const int qsize;//const成员必须初始化
    public:
        Queue(int qs=Q_SIZE);
        bool isempty() const;
        bool isfull () const;
        bool enqueue(const int& item);
        bool dequeue(      int& item);
        int queuecount() const;
        ~Queue();
        friend void abc(Queue& a)
        {
          //友元函数在此处通过a访问类内的私有变量
        }
    };
    Queue::Queue(int qs)//构造函数完成成员变量的初始化
            :qsize(qs),front(nullptr),rear(nullptr),items(0){}
            
        bool Queue::isempty() const//尾部加上const是限制this指针，表示类的成员变量都不可以改变
        {return items==qsize;}
        bool Queue::isfull () const
        {return items==qsize;}
        int Queue::queuecount() const
        {return items;}
    bool Queue::enqueue(const int& item)
    {
        if (isfull())
            return false;
        Node* add=new Node;//?这块用new开辟内存的方法是不是可以换成别的形式？new Node()形式可以么？
        add->item=item;
        add->next=nullptr;
        //上面是将这个node生成了出来，至于这个node是放在了结尾或者是队列中的什么位置，需要进行下面的算法来安排
        if (front==nullptr)
            front=add;
        else
        {
            rear->next=add;
            rear->item=item; //?这行该不该加上，
                             //不加肯定是对的，因为节点已经创建完毕，剩下就是如何用指针将这些节点串联到一个链表中，才是合理的。   
                             //加上是不是对的，目前还是确定不了       
        }
        rear=add;
        return true;
    }
    bool Queue::dequeue(      int& item)
    {
        if (isempty())
            return false;
        item=front->item;//这块是有疑问的，为什么要将即将删除的node的value保存下来呢？
        --items;
        Node* temp=front;
        front=front->next;
        delete temp;
        if (items==0)
        {
            rear=nullptr;
        }   
        return true;
    }
    Queue::~Queue()
    {}
int main(int argc, char const *argv[])
{
    Queue q;
    return 0;
}
