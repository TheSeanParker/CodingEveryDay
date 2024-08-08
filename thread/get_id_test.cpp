//线程ID
#include <thread>
#include <iostream>
#include <sstream>
using namespace std;
void worker_thread_func()
{
	 static int a=0;
	 cout<<"a="<<a<<endl;
	 while(a<4)
	 {
		 a++;
        cout<<"cut in the thread a="<<a<<endl;
	 }
}
int main()
{
	//获取主线程的线程 ID
	std::thread::id main_thread_id = std::this_thread::get_id();
 	//先将 std::thread::id 转换成 std::ostringstream 对
	std::ostringstream oss;
 	oss << main_thread_id;
 	//再将 std::ostringstream 对象转换成 std::string
	std::string str = oss.str();
	//最后将 std::string 转换成整型值
 	int threadid = atol(str.c_str());
 	std::cout << "main thread id1: " << threadid << std::endl;
	std::cout << "main thread id2: " << main_thread_id << std::endl;

	string a="jacobi";
	std::thread t(worker_thread_func);
	//获取线程 t 的 ID
	std::thread::id worker_thread_id = t.get_id();
	std::cout << "worker thread id: " << worker_thread_id << std::endl;
 	// while (true)
	// {
	// 	//权宜之计，让主线程不要提前退出
	// }
	t.join();
	return 0;
}
