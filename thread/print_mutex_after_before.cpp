#include <iostream>
#include <thread>
#include <mutex> 
std::mutex mutex_;
int a=1;
 using namespace std;
void print_block1(int n)
{
    // critical section (exclusive access to std::cout signaled by locking mtx):
    std::cout <<"before block1 a="<<a<<std::endl;
    mutex_.lock();
    for (int i = 0; i < n; ++i)
    {
       a=a+1;
       std::cout <<"in block1 a="<<a <<std::endl;
    }
    std::cout <<"after block1 a="<<a <<std::endl;
    mutex_.unlock();
}
 
 void print_block2(int n)
{
    // critical section (exclusive access to std::cout signaled by locking mtx):
    std::cout <<"before block2 a="<<a<<std::endl;
    mutex_.lock();
    for (int i = 0; i < n; ++i)
    {
         a++;
          std::cout <<"in block2 a="<<a <<std::endl;
    }
    std::cout <<"after block2 a="<<a <<'\n';
    mutex_.unlock();
}
int main(int argc, char* argv[])
{
    a=2;
    std::thread thread1(&print_block1, 10);
    std::thread thread2(&print_block2, 20);
 
    thread1.join();
    thread2.join();
 
    return 0;
}