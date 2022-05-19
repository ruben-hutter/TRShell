#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// get the length of all passed string concatenated
int get_concatenated_length(int num_of_args, char* input_string, ...);
// concatenate all strings and write to output string
// note that output_string must be of succficient length to fit concatenation
void conactenate(int num_of_args, char* output_string, char* input_string, ...);
// malloc an empty string of the specified length
char* get_malloced_empty_string(int length);
// adds a terminator at the beginning of the string to empty it
void make_empty_string(char* input_string);
#endif