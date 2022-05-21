#ifndef PROMPT_H
#define PROMPT_H

#define PROMPT_1 " $ "
#define PROMPT_2 "> "
#define PROMPT_3 " # "
#define SEPARATOR " ● "
#define DELIMITER '/'

// update current working directory
void update_cwd(void);
// crop the current working directory to only the last folder
void crop_cwd(void);
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
