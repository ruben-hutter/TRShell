# include "scanner.h"
# include "string.h"
# include "input.h"
# include <stdlib.h>
# include <stdio.h>

int main(int argc, char **argv) {
    char* test_string = "This is a test string to test the tokenization process!";
    
    struct input_struct input;
    populate_struct(input, test_string);

    int length = strlen(test_string);
    for (int i = 0; i < length; i++) {
        printf(get_next_char(&input));
    }
    exit(0);
}