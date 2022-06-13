#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "string_utils.h"

// get the length of all passed string concatenated
int get_concatenated_length(int num_of_args, ...);

// get the length of all passed string in the va_list concatenated
int v_get_concatenated_length(int num_of_args, va_list input_strings);

// concatenate all strings and write to output string
// note that output_string must be of succficient length to fit concatenation
void concatenate(int num_of_args, char* output_string, ...);

// concatenate all strings in the va_list to output string
// note that output_string must be of sufficient length to fit concatenation
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

// sets a terminator at the position of the first newline
void cut_at_trailing_newline(char* input_string);

// returs true if a string is only whitespace, otherwise false
int is_only_whitespace(const char* input_string);

// shifts the section form reg_start to reg_end one character to the right, leading to a gap at region_start
// indexes are not checked!
void shift_string_right(char* input_string, int region_start, int region_end);

// shifts the section form reg_start to reg_end one character to the left, leading to the char at reggion_start to be overwritten
// indexes are not checked!
void shift_string_left(char* input_string, int region_start, int region_end);

// put a the section from form reg_start to reg_end to the std out using putchar
void put_string_section(char* input_string, int region_start, int region_end);

// searches the list for a unique possible match of the approach and returns the match
// if no match NULL is returned
char* compare_against_list(char* approach, char** entry_list, int list_length);

// returns true iff the input_string starts with the pattern_string
int string_starts_with(const char* input_string, const char* pattern_string);

// checkes if a string is a word
int is_single_word(char* string);

// free string array
void free_string_arr(char** string_arr, int arr_length);

#endif