#include <iostream>
#include <thread>
#include <mutex> 
using namespace std;

std::mutex mutex_;
void print_block(int n, char c)
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (int i = 0; i < n; ++i)
    {
        std::cout << c;
    }
    std::cout << '\n';
}
 
int main(int argc, char* argv[])
{
    std::thread thread1(&print_block, 300, '*');
    std::thread thread2(&print_block, 300, '$');
 
    thread1.join();
    thread2.join();
 
    return 0;
}