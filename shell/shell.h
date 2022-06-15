#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "executor.h"
#include "input_reader.h"
#include "token.h"
#include "buffered_string.h"
#include "init.h"
#include "history.h"
#include "symbol_table.h"

extern int running;

// trshell main function
int main(int argc, char **argv);

// parse and execute a command stored in the char buffer
int parse_and_execute(struct buffered_string* buffered_input);

// free everything, clean up programm
void free_everything(void);

#endif
