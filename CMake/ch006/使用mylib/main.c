#include <stdio.h>

extern int add(int, int);

int main() {
    printf("%d\n", add(1, 2));
    return 0;
}