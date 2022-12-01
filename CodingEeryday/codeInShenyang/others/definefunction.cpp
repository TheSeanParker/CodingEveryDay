#include <stdio.h>  
//#define INPUT  
int main() {
    int a = 0;
    printf("a: %d\n", a);
#ifndef INPUT  
    a = 2;
#else  
    printf("Enter a:");
    scanf("%d", &a);
#endif         
    printf("Value of a: %d\n", a);
}