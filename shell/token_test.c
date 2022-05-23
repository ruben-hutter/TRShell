# include "scanner.h"
# include "string.h"
# include "buffered_string.h"
# include <stdlib.h>
# include <stdio.h>

int main(int argc, char **argv) {
    char* test_string = "            This is not a test string to test the tokenization process!";
    struct buffered_string my_input_struct;
    struct buffered_string* my_pointer = &my_input_struct;
    populate_buffered_string(my_pointer, test_string);
    skip_leading_white_spaces(my_pointer);
    int i;
    char next_char;
    int length = strlen(test_string);
    for (i = 0; i < length; i++) {
        next_char = get_next_char(my_pointer);
        printf("%c\n", next_char);
    }
    exit(0);
}
