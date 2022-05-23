#include "input_reader.h"

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