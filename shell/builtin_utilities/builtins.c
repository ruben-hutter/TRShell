#include "builtins.h"

void builtins(int argc, char** argv) {
    // iterate over builtin utilities
    fprintf(stderr, "Command  Description\n");
    for (int idx = 0; idx < builtin_utility_count; idx++) {
        fprintf(stdout, "%-8d %s",builtin_utilities[idx].name, builtin_utilities[idx].description);
    }
}