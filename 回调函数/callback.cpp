#include <iostream>
using namespace std;
void callbackfunc(int a)
{
          cout<<"birthday="<<a<<endl;
}
void process(void(*callback)(int))
{
      cout<<"process()"<<endl;
      int a=612;
      callback(a);
}
int main(int argc, char const *argv[])
{
         process(callbackfunc);
          return 0;
}

// #include <iostream>

// void programA_FunA1() { printf("I'am ProgramA_FunA1 and be called..\n"); }

// void programA_FunA2() { printf("I'am ProgramA_FunA2 and be called..\n"); }

// void programB_FunB1(void (*callback)()) {
//   printf("I'am programB_FunB1 and be called..\n");
//   callback();
// }

// int main(int argc, char **argv) {
//   programA_FunA1();

//   programB_FunB1(programA_FunA2);
// }
