#include "shell.h"

int main(int argc, char **argv) {
    // init shell
    init_shell();
    
    // string to store users input
    char* input_string;
    
    while(true) {
        print_prompt_1();

        // read user input from stdin
        input_string = read_from_input();

        // check for nullpointer
        if (!input_string) {
            exit(EXIT_SUCCESS);
        }   

        // if string empty or only newline
        if (input_string[0] == '\0' || strcmp(input_string, "\n") == true) {
            free(input_string);
            break;
        }

        // add input string to history
        append_string_to_history(input_string);
        // init new struct representing char buffer for easy processing of the input string
        struct buffered_string buffered_input;
        populate_buffered_string(&buffered_input, input_string);
        // parse input
        parse_and_execute(&buffered_input);
    }
    exit(EXIT_SUCCESS);
}

// parse and execute a command stored in the char buffer
int parse_and_execute(struct buffered_string* buffered_input) {
    // drop leading whitspace from buffer
    skip_leading_white_spaces(buffered_input);

    // get first section of input as token object
    struct token* curr_token = get_next_token(buffered_input);


    while (curr_token && curr_token != &eof_token) {
        // build tree storing command and tokens of the users input
        // build_tree_from_root automatically gets following tokens
        struct tree_node* cmd = build_tree_from_root(curr_token);

        // print tree
        print_command_tree(cmd);

        // check nullpointer
        if (!cmd) {
            break;
        }

        do_simple_command(cmd);
        free_tree_from_root(cmd);

        // process next command
        curr_token = get_next_token(buffered_input);
    }

    return 0;
}
