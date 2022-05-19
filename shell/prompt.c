#include <stdio.h>
#include "colors.h"
#include "shell.h"

#define PROMPT_1 "$ "
#define PROMPT_2 "> "

void print_prompt_1(void) {
    //char* prompt_string = colorize(PROMPT_1, ORANGE);
    fprintf(stderr, PROMPT_1);
}

void print_prompt_2(void) {
    //char* prompt_string = colorize(PROMPT_2, ORANGE);
    fprintf(stderr, PROMPT_2);
}