#ifndef BUILTIN_UTILITIES_H
#define BUILTIN_UTILITIES_H

#include "builtin_utilities/dump.h"
#include "builtin_utilities/cd.h"
#include "builtin_utilities/ht.h"
#include "builtin_utilities/exit.h"
#include "builtin_utilities/clera.h"

// struct for builtin utilities
struct builtin_utility {
    char* name;
    void (*func)(int argc, char** argv);
};

// list of builtin utilities
extern struct builtin_utility builtin_utilities[];
extern int builtin_utility_count;

#endif
