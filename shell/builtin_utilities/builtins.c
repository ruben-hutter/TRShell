#include "builtins.h"

// iterate over builtin utilities
void builtins(int argc, char** argv) {
    fprintf(stderr, "Command              Description\n");
    fprintf(stderr, "=======              ===========\n");
    for (int idx = 0; idx < builtin_utility_count; idx++) {
        fprintf(stdout, "%-20s %s\n",builtin_utilities[idx].name,
                builtin_utilities[idx].description);
    }
}
