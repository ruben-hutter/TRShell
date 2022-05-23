# include "scanner.h"
# include "string.h"
# include "input.h"
# include <stdlib.h>
# include <stdio.h>

int main(int argc, char **argv) {
    char* test_string = "            This is not a test string to test the tokenization process!";
    struct input_struct my_input_struct;
    struct input_struct* my_pointer = &my_input_struct;
    populate_struct(my_pointer, test_string);
    skip_white_spaces(my_pointer);
    int i;
    char next_char;
    int length = strlen(test_string);
    for (i = 0; i < length; i++) {
        next_char = get_next_char(my_pointer);
        printf("%c\n", next_char);
    }
    exit(0);
}
