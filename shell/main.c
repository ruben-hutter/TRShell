#include "main.h"

int main(int argc, char **argv) {
    // array containing the users input
    char* input_string;
    
    while(true) {
        // print prompt string 1 to cli
        print_prompt_1();

        // read user input from cli
        input_string = read_from_input();

        // if pointer is NULL
        if (!input_string) {
            exit(EXIT_SUCCESS);
        }   

        // if string empty or only newline
        if (input_string[0] == '\0' || strcmp(input_string, "\n") == true) {
            free(input_string);
            break;
        }

        // init new struct representing char buffer for easy processing of the input
        struct buffered_string buffered_input;
        populate_buffered_string(&buffered_input, input_string);
        parse_and_execute(&buffered_input);
        free(input_string);
    }
    exit(EXIT_SUCCESS);
}

// parse and execute a command stored in the buffered_input
int parse_and_execute(struct buffered_string* buffered_input) {
    // drop leading whitspace from buffer
    skip_leading_white_spaces(buffered_input);
    struct token* curr_token = get_next_token(buffered_input);
    while (curr_token && curr_token != &eof_token) {
        struct tree_node* cmd = build_tree_from_root(curr_token);

        if (!cmd) {
            break;
        }

        do_simple_command(cmd);
        free_tree_from_root(cmd);
        curr_token = get_next_token(buffered_input);
    }

    return 0;
}
