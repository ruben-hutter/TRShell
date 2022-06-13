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
// note that output_string must be of sufficient length to fit concatenation
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
    input_string[strcspn(input_string, "\n")] = '\0';
}

// returs true if a string is only whitespace, otherwise false
int is_only_whitespace(const char* input_string) {
    while (*input_string != '\0') {
        if (!isspace((unsigned char)*input_string)) {
            return false;
        }
        input_string++;
    }
    return true;
}

// shifts the section form reg_start to reg_end one character to the right, leading to a gap at region_start
// indexes are not checked!
void shift_string_right(char* input_string, int region_start, int region_end) {
    for (int current = region_end; current >= region_start; current--) {
        input_string[current + 1] = input_string[current];
    }
}

// shifts the section form reg_start to reg_end one character to the left, leading to the char at reggion_start to be overwritten
// indexes are not checked!
void shift_string_left(char* input_string, int region_start, int region_end) {
    for (int current = region_start; current <= region_end; current++) {
        input_string[current] = input_string[current + 1];
    }
}

// put a the section from form reg_start to reg_end to the std out using putchar
void put_string_section(char* input_string, int region_start, int region_end) {
    for (int current = region_start; current <= region_end; current++) {
        putchar(input_string[current]);
    }
}

// searches the list for a unique possible match of the approach and returns the match
// if no match NULL is returned
char* compare_against_list(char* approach, char** entry_list, int list_length) {
    int approach_length = strlen(approach);
    bool found = false;
    char* match = NULL;
    // iterate over lsit to find matches
    for (int index = 0; index < list_length; index++) {
        // if not matching -> continue
        if (!string_starts_with(entry_list[index], approach)) {
            continue;
        }
        // if match was previously found -> return NULL as match is not unique
        if (found) {
            print_entry_list(entry_list, list_length);
            return NULL;
        }
        found = true;
        match = get_malloced_copy(entry_list[index]);
    }
    return match;
}

// returns true iff the input_string starts with the pattern_string
int string_starts_with(const char* input_string, const char* pattern_string) {
    if(strncmp(input_string, pattern_string, strlen(pattern_string)) == 0) {
        return true;
    }
    return false;
}

// checkes if a string is a word
int is_single_word(char* string) {
    char space = ' ';
    // check if string contains at least a space
    char* spaces = strchr(string, space);
    if (!spaces) {
        return true;
    }
    // check if something else than spaces after first space
    if (is_only_whitespace(spaces)) {
        return true;
    }
    return false;
}

// free string array
void free_string_arr(char** string_arr, int arr_length) {
    for (int index = 0; index < arr_length; index++) {
        if (string_arr[index]) {
            free(string_arr[index]);
        }
    }
    free (string_arr);
}
