#include "builtin_utilities.h"

struct builtin_utility builtin_utilities[] =
    {
        {"dump", dump},
    };

int builtin_utility_count = sizeof(builtin_utilities)/sizeof(struct builtin_utility);