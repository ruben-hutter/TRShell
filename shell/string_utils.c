#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "string_utils.h"


// get the length of all passed string concatenated
int get_concatenated_length(int num_of_args, ...) {
    // prepare arg list for iteration
    va_list args;
    va_start(args, num_of_args);
    // loop through args and sum length
    int concatenated_length = v_get_concatenated_length(num_of_args, args);
    // end list
    va_end(args);
    // return resulting length
    return concatenated_length;
}

// get the length of all passed string in the va_list concatenated
int v_get_concatenated_length(int num_of_args, va_list input_strings) {
    int concatenated_length = 0;
    int iter;
    for (iter = 0; iter < num_of_args; iter++) {
        concatenated_length += strlen(va_arg(input_strings, char*));
    }
    // return resulting length
    return concatenated_length;
}

// concatenate all strings and write to output string
// note that output_string must be of succficient length to fit concatenation
void concatenate(int num_of_args, char* output_string, ...) {
    // prepare arg list for iteration
    va_list args;
    va_start(args, output_string);
    // concate strings using v_concatenate
    v_concatenate(num_of_args, output_string, args);
    // end list
    va_end(args);
}

// concatenate all strings in the va_list to output string
// note that output_string must be of succficient length to fit concatenation
void v_concatenate(int num_of_args, char* output_string, va_list input_strings) {
    int iter;
    for (iter = 0; iter < num_of_args; iter++) {
        strcat(output_string, va_arg(input_strings, char*));
    }
}

// malloc an empty string of the specified length
char* get_malloced_empty_string(int length) {
    // works as sizeof(char) is qual to 1
    char* colored_string = (char*) malloc(length + 1);
    *colored_string = '\0';
    return colored_string;
}

// adds a terminator at the beginning of the string to empty it
void make_empty_string(char* input_string) {
    *input_string = '\0';
}

// drops all of string before and including last occurence of delimiter
// example for delimiter '&': first&second&third -> third
void crop_string_to_end(char* input_string, char delimiter) {
    // check string length
    int input_len = strlen(input_string);
    // get pointer to end of string
    char* eos_ptr = input_string + input_len;
    // iterate backwrds until delimiter sign
    char* actual_ptr = eos_ptr;
    while (actual_ptr > input_string) {
        if (*actual_ptr == delimiter) {
            // overrite actual string
            strcpy(input_string, actual_ptr+1);
            break;
        }
        actual_ptr--;
    }
}
