#ifndef PRINT_H
#define PRINT_H

#include "print_export.h"

PRINT_EXPORT void print();
PRINT_NO_EXPORT void _internal();

#ifndef PRINT_NO_DEPRECATED
PRINT_DEPRECATED_EXPORT void old_print();
#endif // PRINT_NO_DEPRECATED

#endif // PRINT_H