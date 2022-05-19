#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "colors.h"
#include "shell.h"

#define PROMPT_1 "$ "
#define PROMPT_2 "> "
#define PROMPT_3 "ᐅ # "
#define SEPARATOR " ● "

char current_working_dir[100];

char* construct_prefix(char* user, char* w_dir) {
    int user_length = strlen(user) + strlen(SEPARATOR);
    char user_part[user_length];
    *user_part = '\0';
    strcat(user_part, user);
    strcat(user_part, SEPARATOR);
    char* colored_user_part = colorize(user_part, PRIMARY);

    char* colored_w_dir = colorize(w_dir, SECONDARY);
    char* styled_w_dir = style(colored_w_dir, BOLD);
    free(colored_w_dir);

    int prefix_length = strlen(colored_user_part) + strlen(styled_w_dir) + 1;
    char* prefix = get_malloc_empty_string(prefix_length);
    strcat(prefix, colored_user_part);
    free(colored_user_part);
    strcat(prefix, styled_w_dir);
    free(styled_w_dir);
    strcat(prefix, " ");
    return prefix;
}

void print_prompt_1(void) {
    char* prefix = construct_prefix("tobi", "some_dir");
    char* prompt_string = colorize(PROMPT_1, PRIMARY);

    int prompt_length = strlen(prefix) + strlen(prompt_string);
    char prompt[prompt_length];
    *prompt = '\0';
    strcat(prompt, prefix);
    free(prefix);
    strcat(prompt, prompt_string);
    free(prompt_string);
    fprintf(stderr, prompt);
}

void print_prompt_2(void) {
    char* prompt_string = colorize(PROMPT_2, PRIMARY);
    fprintf(stderr, prompt_string);
    free(prompt_string);
}

// TODO test
void get_pwd(void) {
    if (getcwd(current_working_dir, sizeof(current_working_dir)) != NULL) {
        return;
    }
    perror("getcwd() error");
    return;
}
