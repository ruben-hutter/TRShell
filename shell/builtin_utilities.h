#ifndef BUILTIN_UTILITIES_H
#define BUILTIN_UTILITIES_H

#include "dump.h"
#include "builtin_utilities/cd.h"

// struct for builtin utilities
struct builtin_utility {
    char* name;
    void (*func)(int argc, char** argv);
};

// list of builtin utilities
extern struct builtin_utility builtin_utilities[];
extern int builtin_utility_count;

#endif
