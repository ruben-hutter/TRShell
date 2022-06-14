#include <stdio.h>

#include "string_utils.h"

int main(int argc, char** argv) {
    char* string = "test asdf adsf";
    char* str = insert_char_before_char(string, ' ', '\\');
    printf("string: %s\n", str);
    free(str);
    return 0;
}