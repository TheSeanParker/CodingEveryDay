#include <iostream>
//inheritance 表现出来 is a
//继承最有价值的地方是和虚函数结合在一起
//子类有父类的部分成分在
struct _List_node_base
{
  _List_node_base* _M_next;
  _List_node_base* _M_prev;
};
template<typename _Tp>
struct _List_node : public _List_node_base
{
    /* data */
    _Tp _M_data;
};

int main(int argc, char const *argv[])
{
    /* code */
    
    return 0;
}
