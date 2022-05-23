#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "shell.h"
#include "input.h"
#include "parser.h"
#include "executor.h"
#include "scanner.h"

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
        struct input_struct input;
        populate_struct(&input, input_string);
        parse_and_execute(&input);
        free(input_string);
    }
    exit(EXIT_SUCCESS);
}

// reads user input from the stdin
char* read_from_input() {
    char buffer[1024];
    char* ptr = NULL;
    char ptrlen = 0;

    while (fgets(buffer, 1024, stdin)) {
        int buflen = strlen(buffer); // ex. "ls -al" -> "ls -al\n" (without '\0')

        if (!ptr) {
            // initial buffer allocation
            ptr = malloc(buflen+1);
        } else {
            // increase buffer allocated size
            char *ptr2 = realloc(ptr, ptrlen+buflen+1);
            // if new pointer could be allocated
            if (ptr2) {
                // make old pointer point to new string
                ptr = ptr2;
            } else {
                // free old pointer and return nullpointer
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr) {
            // failed allocating buffer
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        // copy buffered entry to allocated buffer
        strcpy(ptr+ptrlen, buffer);

        if (buffer[buflen-1] == '\n') {
            // last buffer char is "new line"
            if (buflen == 1 || buffer[buflen-2] != '\\') {
                // end of command if empty or not continues on new line
                return ptr;
            }
            // if it continues remove last 2 chars
            ptr[ptrlen+buflen-2] = '\0';
            buflen -= 2;
            print_prompt_2();
        }

        ptrlen += buflen;
    }

    return ptr;
}

// parse and execute a command stored in the string buffer
int parse_and_execute(struct input_struct* input) {
    // drop leading whitspace from buffer
    skip_white_spaces(input);
    struct token_struct* token = tokenize(input);
    // if only contains end of file -> return
    if (token == &eof_token) {
        return 0;
    } 
    // decompose input into sections
    while (token && token != &eof_token) {
        struct node_struct* cmd = parse_simple_command(token);

        if (!cmd) {
            break;
        }

        do_simple_command(cmd);
        free_node_tree(cmd);
        token = tokenize(input);
    }

    return 1;
}
