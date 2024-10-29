#include <iostream>
void swap(int *x, int *y);
int main()
{
    int x = 5, y = 10;
    std::cout << "Main. Before swap, x: " << x 
              << " y: " << y << "\n";
    swap(&x, &y);
    std::cout << "Main. After swap, x: " << x 
              << " y: " << y << "\n";
    return 0;
}
  
void swap(int *px, int *py)
{
    int temp;
    std::cout << "Swap. Before swap, *px: " << *px 
              << " *py: " << *py << "\n";
    std::cout<<"&temp="<<&temp<<std::endl;
    std::cout<<"pX="<<px<<std::endl;
    std::cout<<"pY="<<py<<std::endl;
    std::cout<<"/////////////////////////////////////////////"<<std::endl;
    temp = *px;
    *px = *py;//指针所在的地址并没有发生任何的改变,但是他们所指向地址存放的数值发生了<交换>
    *py = temp;
    std::cout<<"&temp="<<&temp<<std::endl;
    std::cout<<"pX="<<px<<std::endl;
    std::cout<<"pY="<<py<<std::endl;
    std::cout<<"/////////////////////////////////////////////"<<std::endl;
    std::cout << "Swap. After swap, *px: " << *px 
              << " *py: " << *py << "\n";
}
