#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

// put a string between a given char (input_string must me on heap)
void string_bwn_char(char** input_string, char* add_quotes);

int check_buffer_bounds(int* count, int* length, char*** buffer);

void free_buffer(int length, char** buffer);

void cut_at_trailing_newline(char* input_string);

int is_only_whitespace(const char* input_string);

void shift_string_right(char* input_string, int region_start, int region_end);

void shift_string_left(char* input_string, int region_start, int region_end);

void put_string_section(char* input_string, int region_start, int region_end);

// returns true iff the input_string starts with the pattern_string
int string_starts_with(const char* input_string, const char* pattern_string);

// checkes if a string is a word
int is_single_word(char* string);

// free string array
void free_string_arr(char** string_arr, int arr_length);

// remove chars (from given list of chars) from given string
void remove_chars_from_string(char* input_string, char* to_remove);

#endif