#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// get the length of all passed string concatenated
int get_concatenated_length(int num_of_args, ...);

// get the length of all passed string in the va_list concatenated
int v_get_concatenated_length(int num_of_args, va_list input_strings);

// concatenate all strings and write to output string
// note that output_string must be of succficient length to fit concatenation
void concatenate(int num_of_args, char* output_string, ...);

// concatenate all strings in the va_listin to output string
// note that output_string must be of succficient length to fit concatenation
void v_concatenate(int num_of_args, char* output_string, va_list input_strings);

// malloc an empty string of the specified length
char* get_malloced_empty_string(int length);

// gets a malloced copy of the passed string
char* get_malloced_copy(char* input_string);

// adds a terminator at the beginning of the string to empty it
void make_empty_string(char* input_string);

// drops all of string before and including last occurence of delimiter
// example for delimiter '&': first&second&third -> third
void crop_string_to_end(char* input_string, char delimiter);




// delete the char at the specified position
void delete_char_at(char* input_string, size_t char_index);

// subsitiutes the section between start and end of first_string with the second_string
char* subsitute_section_with_string(char* input_string, char* substitute_string, size_t start, size_t end);

// returns a pointer to the first occurence of any of the chars in the chars string
char* is_any_char_present_in(char* input_string, char* chars);

// n puts a string in quotes
char* add_quotes(char* input_string, int add_quotes);

int check_buffer_bounds(int* count, int* length, char*** buffer);

void free_buffer(int length, char** buffer);

void cut_at_trailing_newline(char* input_string);

#endif