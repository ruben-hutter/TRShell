#include "prompt.h"

// print prompt for current user
void print_prompt() {
    // check if root
    char* username = get_user_name();
    if (strcmp("root", username) == 0) {
        print_prompt_3();
        free(username);
        return;
    }
    free(username);
    print_prompt_1();
}

void print_prompt_1() {
    // get username from environment vars
    char* username = get_user_name();
    // get current working dir from environment vars
    char* pwd = get_current_working_dir();
    // get prefix and prompt
    char* prefix = create_user_prefix(username, pwd);
    free(username);
    free(pwd);
    // get prompt symbol
    char* prompt = create_user_prompt(get_prompt_symbol_1());
    // combine prefix and prompt to prompt_string
    char prompt_string[get_concatenated_length(2, prefix, prompt)];
    make_empty_string(prompt_string);
    concatenate(2, prompt_string, prefix, prompt);
    free(prefix);
    free(prompt);
    // print prompt string
    printf(prompt_string);
}

// gets the prompt symbol for prompt 1
char* get_prompt_symbol_1() {
    char* ps1 = get_local_table_entry_value("PS1");
    if (!ps1) {
        ps1 = PROMPT_1;
    }
    return ps1;
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

// gets the username of the current user
char* get_user_name(void) {
    char* name = get_local_table_entry_value("USER");
    if (!name) {
        name = USER_PLACEHOLDER;
    }
    char* user_name = get_malloced_copy(name);
    return user_name;
}

// gets the current working dir
char* get_current_working_dir() {
    // get PWD from environment vars
    char* pwd = get_local_table_entry_value("PWD");
    if (!pwd) {
        // if not found -> return placeholder
        return PWD_PLACEHOLDER;
    }
    char* dir_name = get_malloced_copy(pwd);
    crop_string_to_end(dir_name, '/');
    // check if dir is home
    char* username = get_user_name();
    if (strcmp(dir_name, username) == 0) {
        strcpy(dir_name, HOME);
    }
    free(username);
    return dir_name;
}

void print_prompt_2() {
    char* prompt_string = create_user_prompt(PROMPT_2);
    printf(prompt_string);
    free(prompt_string);
}

void print_prompt_3() {
    // get username from environment vars
    char* username = "root";
    // get current working dir from environment vars
    char* pwd = get_current_working_dir();
    // get prefix and prompt
    char* prefix = create_root_prefix(username, pwd);
    free(pwd);
    // get prompt symbol
    char* prompt = create_root_prompt(get_prompt_symbol_3());
    // combine prefix and prompt to prompt_string
    char prompt_string[get_concatenated_length(2, prefix, prompt)];
    make_empty_string(prompt_string);
    concatenate(2, prompt_string, prefix, prompt);
    free(prefix);
    free(prompt);
    // print prompt string
    printf(prompt_string);
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

// gets the prompt symbol for prompt 1
char* get_prompt_symbol_3() {
    char* ps3 = get_local_table_entry_value("PS3");
    if (!ps3) {
        ps3 = PROMPT_3;
    }
    return ps3;
}



// -----------------------------------------------------------------------------
// Check later as not important now!
// -----------------------------------------------------------------------------


/*
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
*/


