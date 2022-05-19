#include <stdarg.h>
# include "string.h"

# include "string_utils.h"

// get the length of all passed string concatenated
int get_concatenated_length(int num_of_args, char* input_string, ...) {
    // prepare arg list for iteration
    va_list args;
    va_start(args, input_string);
    // loop through args and sum length
    int concatenated_length = 0;
    int iter;
    for (iter = 0; iter < num_of_args; iter++) {
        concatenated_length += strlen(va_arg(args, char*));
    }
    // end list
    va_end(args);
    // return resulting length
    return concatenated_length;
}

// concatenate all strings and write to output string
// note that output_string must be of succficient length to fit concatenation
void conactenate(int num_of_args, char* output_string, char* input_string, ...) {
    // prepare arg list for iteration
    va_list args;
    va_start(args, input_string);
    // loop through args and sum length
    int iter;
    for (iter = 0; iter < num_of_args; iter++) {
        strcat(output_string, va_arg(args, char*));
    }
    // end list
    va_end(args);
}
