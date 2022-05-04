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

char* read_command(void) {
    char buf[1024];
    char* ptr = NULL;
    char ptrlen = 0;

    while (fgets(buf, 1024, stdin)) {
        int buflen = strlen(buf);

        if (!ptr) {
            ptr = malloc(buflen+1);
        } else {
            char *ptr2 = realloc(ptr, ptrlen+buflen+1);

            if (ptr2) {
                ptr = ptr2;
            } else {
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr) {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr+ptrlen, buf);

        if (buf[buflen-1] == '\n') {
            if (buflen == 1 || buf[buflen-2] != '\\') {
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