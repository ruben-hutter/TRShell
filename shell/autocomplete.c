#include "autocomplete.h"

char* last_approach = NULL;
int last_approach_size = DEFAULT_RESULT_SIZE;
int last_approach_index = 0;

char** dir_querry_result = NULL;
int dir_querry_result_size = DEFAULT_RESULT_SIZE;
int dir_querry_result_index = 0;

char** binary_querry_result = NULL;
int binary_querry_result_size = DEFAULT_RESULT_SIZE;
int binary_querry_result_index = 0;

// tries to autocomplete the approach and returns the completed version if found
// if no single answer is found all answers are printed to the terminal and the received approach is copied to the current buffer
char* autocomplete(char* approach) {
    // free previous approach cache
    if (last_approach) {
        free(last_approach);
    }
    // update prvious approach cache
    last_approach = get_malloced_copy(approach);

    // get last token of input
    int token_count = 0;
    // Extract the first token
    char * token = strtok(last_approach, " ");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
        token = strtok(NULL, " ");
    }

    // search for binaries containig the last token in their name
    switch (querry_binaries(token))
    {
    case 0:
        // no result found
        break;
    case 1:
        // single result found
        break;
    default:
        // multiple results found
        break;
    }


    
}

// querries the requested path for all files and directories
int querry_directories_and_files(char* path) {
    if (dir_querry_result) {
        free(dir_querry_result);
    }
    // create buffer structure to store results
    if (!dir_querry_result) {
        dir_querry_result = malloc(dir_querry_result_size*sizeof(char*)); 
    }
    if (dir_querry_result_index >= dir_querry_result_size) {
        // increase buffers allocated size
        char** new_result = realloc(dir_querry_result, 2*dir_querry_result_size*sizeof(char*));
            // check for failed allocation
            if (new_result) {
                dir_querry_result = new_result;
            } else {
                free(dir_querry_result);
                dir_querry_result = NULL;
            }
    }

    //TODO... call ls to get file and dirs

}

// querries the $PATH in the symbol table for programms starting with the approach
// full name is returne if found
int querry_binaries(char* approach) {
    if (binary_querry_result) {
        free(binary_querry_result);
    }
    // create buffer structure to store results
    if (!binary_querry_result) {
        binary_querry_result = malloc(binary_querry_result_size*sizeof(char*)); 
    }
    if (binary_querry_result_index >= binary_querry_result_size) {
        // increase buffers allocated size
        char** new_result = realloc(binary_querry_result, 2*binary_querry_result_size*sizeof(char*));
            // check for failed allocation
            if (new_result) {
                binary_querry_result = new_result;
            } else {
                free(binary_querry_result);
                binary_querry_result = NULL;
            }
    }

    // iterate over path in symbol table
    // get comma seperated list of directories
    char* PATH = get_local_table_entry_value("PATH");
    if (!PATH) {
        return 0;
    }
    // pointer to beginning of element
    char* entry_start = PATH;
    // pointer to end of element
    char* entry_end;
    // iterate through entries
    while (entry_start && *entry_start) {
        // both pointers at start of entry
        entry_end = entry_start;

        // move end pointer back until the end of entry
        while (*entry_end && *entry_end != ':') {
            entry_end++;
        }

        // get length of entry
        int entry_length = entry_end - entry_start;
        if (!entry_length) {
            entry_length = 1;
        }

        // prepare string to store path
        char path[entry_length+1];

        // copy entry to path
        strncpy(path, entry_start, entry_end-entry_start);
        path[entry_end-entry_start] = '\0';

        //TODO... call ls to get binaries

        // move pointers to start of next entry
        entry_start = entry_end;

        // if one char before first char of next entry -> move one forwad
        if (*entry_end == ':') {
            entry_start++;
        }
    }

    errno = ENOENT;
    return NULL;
}