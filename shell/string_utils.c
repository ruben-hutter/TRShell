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

// gets a malloced copy of the passed string
char* get_malloced_copy(char* input_string) {
    int input_length = strlen(input_string);
    char* output_string = get_malloced_empty_string(input_length);
    strcpy(output_string, input_string);
    return output_string;
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

// sets a terminator at the position of the first newline
void cut_at_trailing_newline(char* input_string) {
    input_string[strcspn(input_string, "\n")] = 0;
}

// returs 1 if a string is only whitespace and zero otherwise
int is_only_whitespace(const char* input_string) {
    while (*input_string != '\0') {
    if (!isspace((unsigned char)*input_string))
      return 0;
    input_string++;
  }
  return 1;
}

// shifts the section form reg_start to reg_end one character to the right, leading to a gap at region_start
// indexes are not checked!
void shift_string_right(char* input_string, int region_start, int region_end) {
    for (int current = region_end; current >= region_start; current--) {
        input_string[current + 1] = input_string[current];
    }
}

// put a the section from form reg_start to reg_end to the std out using putchar
void put_string_section(char* input_string, int region_start, int region_end) {
    for (int current = region_start; current <= region_end; current++) {
        putchar(input_string[current]);
    }
}
