#include <stdio.h>

#include "shell.h"

void print_prompt_1(void) {
    fprintf(stderr, "$ ");
}

void print_prompt_2(void) {
    fprintf(stderr, "> ");
}