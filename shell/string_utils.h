#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// get the length of all passed string concatenated
int get_concatenated_length(int num_of_args, char* input_string, ...);
// get the length of all passed string in the va_list concatenated
int v_get_concatenated_length(int num_of_args, va_list input_strings)
// concatenate all strings and write to output string
// note that output_string must be of succficient length to fit concatenation
void concatenate(int num_of_args, char* output_string, char* input_string, ...);
// concatenate all strings in the va_listin to output string
// note that output_string must be of succficient length to fit concatenation
void v_concatenate(int num_of_args, char* output_string, va_list input_strings);
// malloc an empty string of the specified length
char* get_malloced_empty_string(int length);
// adds a terminator at the beginning of the string to empty it
void make_empty_string(char* input_string);
#endif