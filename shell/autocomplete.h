#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <stdbool.h>
#include <dirent.h>

#include "string_utils.h"
#include "history.h"
#include "builtin_utilities.h"

#define DEFAULT_LENGTH 10

struct approach_split {
    char* pre;
    char* path;
    char* n_complete;
};

// tries to autocomplete the approach and returns the completed version if a unique one exists
// returns NULL if none or multiple possible matches are found.
// multiple matches ar printed to the command line
char* autocomplete(char* approach);

// updates the last_approach with a malloced copy of the current one
void update_last_approach(char* approach);

// returns the single matching history entry if existing
// returns null on single or multiple matches
char* querry_history(char* approach);

// returns the single matching directories if existing
// returns null on single or multiple matches
char* querry_directories(char* approach);

// returns a list of all binaries at the locations specified in PATH
char** get_binaries(int* binaries_length);

// append the names of all files and directories at the specified path to the list
void append_names_to_list(char* path, char** name_list, int* name_list_length, int* name_list_index);

// appends the naems of all builtin utilities to the list
void append_builtin_utilities_to_list(char** name_list, int* name_list_length, int* name_list_index);

// returns the single matching binaries if existing
// returns null on single or multiple matches
char* querry_binaries(char* approach);

// searches the list for a unique possible match of the approach and returns the match
// if no match NULL is returned
char* compare_against_list(char* approach, char** entry_list, int list_length);

// returns true iff the input_string starts with the pattern_string
bool string_starts_with(const char* input_string, const char* pattern_string);

// prints all entries of a list in a ls like fashion to the std out
void print_matching_entries_from_list(char** entry_list, int list_length, char* approach);

// frees an approach split object
void free_approach_split(struct approach_split* ap_split);

#endif