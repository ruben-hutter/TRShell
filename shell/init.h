#ifndef INIT_H
#define INIT_H

#include <string.h>

#include "shell.h"
#include "symbol_table.h"

extern char** environ;

// add all environment variables to the symbol table
void init_shell();

#endif
