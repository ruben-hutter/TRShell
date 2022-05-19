#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "string_utils.h"

int main(int argc, char **argv) {
    char* first = "1234567";
    char* second = "__89010_";
    char conct_str[get_concatenated_length(2, first, second)];
    make_empty_string(conct_str);
    concatenate(2, conct_str, first, second);
    fprintf(stderr, conct_str);
    return 0;
}