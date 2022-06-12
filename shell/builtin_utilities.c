#include "builtin_utilities.h"

struct builtin_utility builtin_utilities[] =
    {
        {"dump", "prints all key-value pairs in the symbol table", dump},
        {"cd", "used to change the current working directory", cd},
        {"ht", "prints an indexed list of the history", ht},
        {"exit", "exits the shell", exit_shell},
        {"clera", "prints a funny line when typo in clear", clera},
    };

int builtin_utility_count = sizeof(builtin_utilities)/sizeof(struct builtin_utility);