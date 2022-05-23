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

// parse and execute a command stored in the buffered_input
int parse_and_execute(struct buffered_string* buffered_input) {
    // drop leading whitspace from buffer
    skip_leading_white_spaces(buffered_input);
    struct token* token = get_next_token(buffered_input);
    // if only contains end of file -> return
    if (token == &eof_token) {
        return 0;
    } 
    // build command tree from buffered input
    while (token && token != &eof_token) {
        struct tree_node* cmd = build_tree_from_root(token);

        if (!cmd) {
            break;
        }

        do_simple_command(cmd);
        free_tree_from_root(cmd);
        token = get_next_token(buffered_input);
    }

    return 1;
}
