#include <iostream>
#include <thread>
#include <mutex> 
std::mutex mutex_;
 using namespace std;
void print_block(int n, char c)
{
    // critical section (exclusive access to std::cout signaled by locking mtx):
    mutex_.lock();
    for (int i = 0; i < n; ++i)
    {
        std::cout << c;
    }
    std::cout << '\n';
    mutex_.unlock();
}
 
int main(int argc, char* argv[])
{
    std::thread thread1(&print_block, 300, '*');
    std::thread thread2(&print_block, 300, '$');
 
    thread1.join();
    thread2.join();
 
    return 0;
}