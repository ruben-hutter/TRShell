#include <stdio.h>
#include <string.h>

#include "string_utils.h"

int main() {
    // test string crop
    char string[100] = "/home/ruben";
    char delimiter = '/';
    char* delim_ptr = &delimiter;
    printf("string before crop: %s\n", string);
    crop_string_to_end(string, delim_ptr);
    printf("string after crop: %s\n", string);
}