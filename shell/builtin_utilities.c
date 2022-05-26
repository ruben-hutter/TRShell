#include "builtin_utilities.h"

int builtin_utility_count = sizeof(builtin_utilities)/sizeof(struct builtin_utility);

struct builtin_utility builtin_utilities[] =
    {
        {"dump", dump},
    };
