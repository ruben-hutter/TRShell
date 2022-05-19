#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "colors.h"
#include "shell.h"

#define PROMPT_1 "tobi :: TRShell ᐅ $ "
#define PROMPT_2 "> "

char* current_working_dir[100];

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

void get_pwd(void) {
    if (getcwd(current_working_dir, sizeof(current_working_dir)) != NULL) {
        return;
    }
    perror("getcwd() error");
    return NULL;
}
