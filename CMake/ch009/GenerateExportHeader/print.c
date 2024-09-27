#include "print.h"
#include <stdio.h>

void print() { printf("Hello\n"); }
void _internal() {}

#ifndef PRINT_NO_DEPRECATED
void old_print() { printf("Hi\n"); }
#endif // PRINT_NO_DEPRECATED