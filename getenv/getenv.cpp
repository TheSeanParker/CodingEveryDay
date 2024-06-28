//  #include <stdlib.h>
// #include <string>
// #include <iostream>

// int main(int cc,char**aa,char**ee)
// // int main(int argc, char ** argv)
// {
//          std::string a;
//          a=std::getenv("HOME") ;
//          std::cout<<a<<std::endl;
         
//           std::cout<<"*aa="<<*aa<<std::endl;
//           std::cout<<"*ee="<<*ee<<std::endl;

//           return 0;
// }

#include <iostream>
#include <unistd.h>
using namespace std;
int main(){
	const int size = 255;
	char buf[size];
	getcwd(buf,size);
	cout<<"Working path is: "<<buf<<endl;
	
	// // buf为空指针时
	// char* buf1 = NULL;
	// buf1 = getcwd(NULL, 0);
	// puts(buf1); // 在屏幕输出该路径
	// free(buf1); // 使用完路径释放buf1，因为是由getcwd()函数动态分配的内存（malloc）
	// // 此时任然可以查看路径占用了多少字节
	// cout << "size is: " << sizeof(buf1) << std::endl;
          cout << "size is: " << sizeof(buf) << std::endl;
          // free(buf);
          cout << "size is: " << sizeof(buf) << std::endl;

	return 0;
}
/*
#include<iostream>
#include<unistd.h> // 函数所在头文件
using namespace std;
int main()	{
	char* buf;
	buf = get_current_dir_name();
	cout << "Current dir name is: " << buf<<endl;
	cout << "size is: " << sizeof(buf) <<endl;
	free(buf); // 一定记得free,因为是由get_current_dir_name()函数动态分配的内存
	return 0;
}
*/
