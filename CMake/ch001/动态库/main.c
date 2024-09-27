#include "liba.h"
#include <stdio.h>

void b() {}
int y = 3;

int main() {
    a();
    printf("&a: %llx\n", (unsigned long long)&a);
    printf("&b: %llx\n", (unsigned long long)&b);
    printf("&y: %llx\n", (unsigned long long)&y);
    getchar();
    return 0;
}