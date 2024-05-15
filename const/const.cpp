

// 该函数接受一个int对象，然后将对象的值设置为0
// void reset(int &i)        
// {
// 	i = 0;               // 改变了i所引对象的值
// }
// int main(int argc, char const *argv[])
// {
//           /* code */
//           // 直接传入对象，无需传递对象的地址
//           int j = 3;
//           reset(j);               // j使用传引用，值被改变
//           return 0;
// }

#include<iostream>
int main()
{
           int a = 1;
   	 const int & b1 = a;  
   	 int & b2 = b1;
}

// #include<iostream>
// #include<string>
// using std::cout;
// using std::string;
// using std::endl;
// void PrintStr(std::string& str);
// void f(const int  &a)
// {
//           cout<<"a="<<endl;
// }
// int main()
// {
//      string A=("HelloWorld!");
//      int a=1;
//      int b=2;
//     PrintStr(A);   //string("HelloWorld!")  为一个临时变量
//     f(a+b);
//     return 0;
// }
// void PrintStr(std::string& str)
// {
//     cout<< str << endl;
// }

