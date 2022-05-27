#ifndef BUILTIN_UTILITIES_H
#define BUILTIN_UTILITIES_H

#include "dump.h"

// struct for builtin utilities
struct builtin_utility {
    char* name;
    int (*func)(int argc, char** argv);
};

// list of builti utilities
extern struct builtin_utility builtin_utilities[];
extern int builtin_utility_count;

#endif
