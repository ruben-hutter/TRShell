#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "executor.h"
#include "input_reader.h"
#include "token.h"
#include "buffered_string.h"

void print_prompt_1(void);
void print_prompt_2(void);
int main(int argc, char **argv);
int parse_and_execute(struct buffered_string* buffered_input);

#endif
