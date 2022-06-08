#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "string_utils.h"
#include "symbol_table.h"

#define DEFAULT_RESULT_SIZE 10

// stores the last called approach
char* last_approach;
int last_approach_size;
int last_approach_index;

char** dir_querry_result;
int dir_querry_result_size;
int dir_querry_result_index;

char** binary_querry_result;
int binary_querry_result_size;
int binary_querry_result_index;

// tries to autocomplete the approach and returns the completed version if found
// if no single answer is found all answers are printed to the terminal and the received approach is copied to the current buffer
char* autocomplete(char* approach);
// querries the requested path for all files and directories
int querry_directories_and_files(char* path);
// querries the $PATH in the symbol table for programms starting with the approach
// full name is returne if found
int querry_binaries(char* approach);

#endif