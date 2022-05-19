#include <iostream>
//不含有指针pointer
        // class shallow 
        // { 
        //     public: 
        //         shallow(int _data) : data(_data){} 
        //         shallow(){}
            
        //         int data;
        // };
        // int main() 
        // { 
        //     shallow a(5), b = a; // 仅仅是数据成员之间的赋值 
        //     std::cout<<"Output="<<b.data<<std::endl;
        // }
        // 这一句b = a;就是浅拷贝，执行完这句后b.data = 5;
        // 如果对象中没有其他的资源（如：堆，文件，系统资源等），则深拷贝和浅拷贝没有什么区别，
        // 但当对象中有这些资源时，例子：
//含有指针pointer
class shallow 
{ 
	public: 
	shallow(int _size) : size(_size)
	{
		data = new int[size];
	} // 假如其中有一段动态分配的内存 
	shallow(){std::cout<<"no para func be called"<<std::endl;};
	shallow(const shallow& _A) : size(_A.size)
	{
		data = new int[size];
	} // 深拷贝 
	~shallow()
	{
		delete [] data;
	} // 析构时释放资源
          int* data; 
          int size;
 };
int main() 
{ 
    shallow a(5); // 注意这一句 
    std::cout<<"a.data="<<a.data<<";a.size="<<a.size<<std::endl;
    shallow b=a;
    std::cout<<"b.data="<<b.data<<";b.size="<<b.size<<std::endl;
    //std::cout<<"b.data="<<b.data<<";b.size="<<b.size<<std::endl;
}