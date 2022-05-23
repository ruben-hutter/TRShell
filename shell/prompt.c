#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "prompt.h"
#include "colors.h"
#include "shell.h"
#include "string_utils.h"

char current_working_dir[100];
char* last_folder;

// update current working directory
void update_cwd(void) {
    if (getcwd(current_working_dir, sizeof(current_working_dir)) != NULL) {
       return;
    }
    perror("getcwd() error");
    return;
}

// checks if currently in home, if so, replace with tilde
void check_if_home(void) {
    char name[20];
    get_login_r(name, sizeof(name));
    printf("current: %s\n", current_working_dir);
    if (strcmp(name, current_working_dir) == 0) {
        strcpy(current_working_dir, "~");
    }
}

// get the prompt prefix containing the user name and the current directory in user colors
char* create_user_prefix(char* user_name, char* curr_work_dir_name) {
    // construct styled version of username + separator
    char user_part[get_concatenated_length_with_style(3, USER_PRIMARY, user_name, SEPARATOR)];
    make_empty_string(user_part);
    concatenate_with_style(3, user_part, USER_PRIMARY, user_name, SEPARATOR);

    // construct styled version of working directory
    char dir_part[get_concatenated_length_with_style(3, USER_SECONDARY, STYLE_BOLD, curr_work_dir_name)];
    make_empty_string(dir_part);
    concatenate_with_style(3, dir_part, USER_SECONDARY, STYLE_BOLD, curr_work_dir_name);

    // concatenate user_part and dir_part
    char* prefix = get_malloced_empty_string(get_concatenated_length(2, user_part, dir_part));
    concatenate(2, prefix, user_part, dir_part);

    return prefix;
}

//  get the prompt symbol of the specified prompt in user colors
char* create_user_prompt(char* prompt) {
    char* styled_prompt = get_malloced_empty_string(get_concatenated_length_with_style(2, prompt, USER_PRIMARY));
    concatenate_with_style(2, styled_prompt, USER_PRIMARY, prompt);
    return styled_prompt;
}

// get the prompt prefix containing the user name and the current directory in user colors
char* create_root_prefix(char* user_name, char* curr_work_dir_name) {
    // construct styled version of username + separator
    char user_part[get_concatenated_length_with_style(3, ROOT_PRIMARY, user_name, SEPARATOR)];
    make_empty_string(user_part);
    concatenate_with_style(3, user_part, ROOT_PRIMARY, user_name, SEPARATOR);

    // construct styled version of working directory
    char dir_part[get_concatenated_length_with_style(3, ROOT_SECONDARY, STYLE_BOLD, curr_work_dir_name)];
    make_empty_string(dir_part);
    concatenate_with_style(3, dir_part, ROOT_SECONDARY, STYLE_BOLD, curr_work_dir_name);

    // concatenate user_part and dir_part
    char* prefix = get_malloced_empty_string(get_concatenated_length(2, user_part, dir_part));
    concatenate(2, prefix, user_part, dir_part);

    return prefix;
}

//  get the prompt symbol of the specified prompt in user colors
char* create_root_prompt(char* prompt) {
    char* styled_prompt = get_malloced_empty_string(get_concatenated_length_with_style(2, prompt, ROOT_PRIMARY));
    concatenate_with_style(2, styled_prompt, ROOT_PRIMARY, prompt);
    return styled_prompt;
}


void print_prompt_1(void) {
    // update the current working directory
    update_cwd();
    // crop to last folder
    crop_string_to_end(current_working_dir, DELIMITER);

    // check if in home
    // TODO: PLEASE NO HIDDEN SIDEEFFECTS
    // either replace_home_with_tilde(char* curr_dir) or move to update_cwd(...)
    // crop_string_...(...) could also be moved
    check_if_home();
    
    // get prefix and prompt
    char* prefix = create_user_prefix("tobi", "test");
    char* prompt = create_user_prompt(PROMPT_1);
    // combine prefix and prompt to prompt_string
    char prompt_string[get_concatenated_length(2, prefix, prompt)];
    make_empty_string(prompt_string);
    concatenate(2, prompt_string, prefix, prompt);
    // free prefix and prompt
    free(prefix);
    free(prompt);
    // print prompt string
    fprintf(stderr, prompt_string);
}

void print_prompt_2(void) {
    char* prompt_string = create_user_prompt(PROMPT_2);
    fprintf(stderr, prompt_string);
    free(prompt_string);
}

void print_prompt_3(void) {
    // update the current working directory
    update_cwd();
    // crop to last folder
    crop_string_to_end(current_working_dir, '/');
    // check if in home
    check_if_home();
    // get prefix and prompt
    char* prefix = create_user_prefix("tobi", last_folder);
    char* prompt = create_user_prompt(PROMPT_3);
    // combine prefix and prompt to prompt_string
    char prompt_string[get_concatenated_length(2, prefix, prompt)];
    make_empty_string(prompt_string);
    concatenate(2, prompt_string, prefix, prompt);
    // free prefix and prompt
    free(prefix);
    free(prompt);
    // print prompt string
    fprintf(stderr, prompt_string);
}
