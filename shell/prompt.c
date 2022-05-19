#include <stdio.h>
#include "colors.h"
#include "shell.h"
# include <stdlib.h>

#define PROMPT_1 "tobi :: TRShell ᐅ $ "
#define PROMPT_2 "> "

void print_prompt_1(void) {
    char* prompt_string = colorize(PROMPT_1, ORANGE);
    fprintf(stderr, prompt_string);
    free(prompt_string);
}

void print_prompt_2(void) {
    char* prompt_string = colorize(PROMPT_2, ORANGE);
    fprintf(stderr, prompt_string);
    free(prompt_string);
}