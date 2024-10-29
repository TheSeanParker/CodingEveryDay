#include <iostream>
void swap(int x, int y);
int main()
{
    int x = 5, y = 10;
    std::cout << "Main. Before swap, x: " << x 
              << " y: " << y << "\n";
    swap(x,y);// 主要原因是输入的X和Y进到函数里后,就成为局部变量了
    std::cout << "Main. After swap, x: " << x 
              << " y: " << y << "\n";
    return 0;
}
  
void swap (int x, int y)
{
    int temp;
    std::cout << "Swap. Before swap, x: " << x 
              << " y: " << y << "\n";
    std::cout<<"&temp="<<&temp<<std::endl;
    std::cout<<"&x="<<&x<<std::endl;
    std::cout<<"&y="<<&y<<std::endl;
    std::cout<<"/////////////////////////////////////////////"<<std::endl;
    temp = x;
    x = y;
    y = temp;
    std::cout<<"&temp="<<&temp<<std::endl;
    std::cout<<"&x="<<&x<<std::endl;
    std::cout<<"&y="<<&y<<std::endl;
    std::cout<<"/////////////////////////////////////////////"<<std::endl;
    std::cout << "Swap. After swap, x: " << x 
              << " y: " << y << "\n";
}
