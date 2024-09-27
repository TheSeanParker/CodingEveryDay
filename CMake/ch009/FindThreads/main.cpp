#include <cstdio>
#include <thread>

void worker(int i) { printf("worker%d\n", i); }

int main() {
    std::thread th(worker, 0);
    th.join();
    return 0;
}