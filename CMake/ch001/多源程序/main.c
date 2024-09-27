#include <stdio.h>

extern const char *msg;

int main() {
    printf("%s\n", msg);
    return 0;
}