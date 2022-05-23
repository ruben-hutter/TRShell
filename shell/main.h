#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "parser.h"
#include "executor.h"
#include "token_builder.h"
#include "buffered_string.h"

void print_prompt_1(void);
void print_prompt_2(void);
int main(int argc, char **argv);
char* read_from_input();
int parse_and_execute(struct buffered_string* buffered_input);

#endif
