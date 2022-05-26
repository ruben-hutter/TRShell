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

// function prototypes of shell
int main(int argc, char **argv);
int parse_and_execute(struct buffered_string* buffered_input);

#endif
