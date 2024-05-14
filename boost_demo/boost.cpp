#include <iostream>
 
#include <boost/thread/thread.hpp> 
#include <boost/thread/mutex.hpp> 
 
boost::mutex mutex;
 
void print_block(int n, char c)
{
    // critical section (exclusive access to std::cout signaled by locking mtx):
    mutex.lock();
    for (int i = 0; i < n; ++i)
    {
        std::cout << c;
    }
    std::cout << '\n';
    mutex.unlock();
}
 
int main(int argc, char* argv[])
{
    boost::thread thread1(&print_block, 300, '*');
    boost::thread thread2(&print_block, 300, '$');
 
    thread1.join();
    thread2.join();
 
    return 0;
}