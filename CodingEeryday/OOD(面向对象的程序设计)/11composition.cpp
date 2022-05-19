#include <iostream>
#include <deque>
#include <vector>
#include <stack>
//composition(复合) ，表示为has a
template <class T>
class queue//队列，是先进先出
{
    protected: 
          std::deque<T> d;//底层容器,功能强大，两端都可以进出
    public:
    
    bool empty() const { return d.empty();}
    std::size_t size() const {return d.size();}
    //reference front(){return d.front();}
    //reference back(){return d.back();}
    //void push(const value_type& x){return d.push_back;}
    void pop(){d.pop_front();}
};
//以上情况就表现出一种设计模式，叫做Adapter 变压器，适配器；queue就是一个adapter 
int main(int argc, char const *argv[])
{
    /* code */
    queue<double> b;
    std::cout<<b.size()<<std::endl;
    return 0;
}
