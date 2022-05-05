#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "shell.h"

int main(int argc, char **argv) {
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

        // print entered input for debug purposes
        printf("%s\n", input_string);
        free(input_string);
    }
    exit(EXIT_SUCCESS);
}

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

            if (ptr2) {
                ptr = ptr2;
            } else {
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

            ptr[ptrlen+buflen-2] = '\0';
            buflen -= 2;
            print_promt_2();
        }

        ptrlen += buflen;
    }

    return ptr;
}