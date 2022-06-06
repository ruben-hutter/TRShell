#ifndef PROMPT_H
#define PROMPT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "colors.h"
#include "shell.h"
#include "string_utils.h"

#define PROMPT_1 " $ "
#define PROMPT_2 "> "
#define PROMPT_3 " # "
#define SEPARATOR " ● "
#define DELIMITER '/'

#define USER_PLACEHOLDER "no_user_name"
#define PWD_PLACEHOLDER "no_pwd"
#define HOME "~"

// gets the username of the current user
char* get_user_name(void);
// gets the current working dir
char* get_current_working_dir(void);
// gets the prompt symbol for prompt 1
char* get_prompt_symbol_1(void);
// get the prompt prefix containing the user name and the current directory in user colors
char* create_user_prefix(char* user_name, char* curr_work_dir_name);
//  get the prompt symbol of the specified prompt in user colors
char* create_user_prompt(char* prompt);
// get the prompt prefix containing the user name and the current directory in user colors
char* create_root_prefix(char* user_name, char* curr_work_dir_name);
//  get the prompt symbol of the specified prompt in user colors
char* create_root_prompt(char* prompt);
// prints prompt string 1
void print_prompt_1(void);
// prints prompt string 2
void print_prompt_2(void);
//prints prompt string 3
void print_prompt_3(void) ;

#endif
