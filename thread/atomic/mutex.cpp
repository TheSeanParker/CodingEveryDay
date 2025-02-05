#include <iostream>
#include <thread>
#include <atomic>
#include <time.h>
#include <mutex>
using namespace std;
 
#define MAX 100000
#define THREAD_COUNT 20
 
int total = 0;
mutex mt;
 
void thread_task()
{
    for (int i = 0; i < MAX; i++)
    {
        mt.lock();
        total += 1;
        total -= 1;
        mt.unlock();
    }
}
 
int main()
{
    clock_t start = clock();
    thread t[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        t[i] = thread(thread_task);
    }
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        t[i].join();
    }
    
    clock_t finish = clock();
    // 输出结果
    cout << "result:" << total << endl;
    cout << "duration:" << finish - start << "ms" << endl;
 
    return 0;
}
