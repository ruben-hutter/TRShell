#include <stdio.h>

#include "string_utils.h"

#define DEFAULT_LENGTH 10

int main(int argc, char** argv) {
    char* string = "cd q";
    char* str = get_malloced_copy(string);

    free(str);
    return 0;
}

// returns a list of all binaries at the locations specified in PATH
char** get_binaries(int* bin_lst_idx) {
    // create list to store dir and file names
    char** binaries = (char**) malloc(DEFAULT_LENGTH * sizeof(char*));
    // current mex cap of the list
    int bin_cnt = DEFAULT_LENGTH;
    int* bin_cnt_ptr = &bin_cnt;
    // current insert position in the list
    *bin_lst_idx = 0;
    // add dir and file names to list
    // get comma seperated list of directories
    char* env_path = get_local_table_entry_value("PATH");

    char* delimiter = ":";
    char* entry = strtok(env_path, delimiter);
    while (entry != NULL) {
        printf("actual token: %s\n", entry);
        entry = strtok(NULL, delimiter);
    }

    // pointer to beginning of element
    char* entry_start = env_path;
    // pointer to end of element
    char* entry_end;
    // iterate through entries
    while (entry_start && *entry_start) {
        // get path to binaries
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
        // create empty string to contain path
        char path[entry_length];      
        // copy entry to path
        strncpy(path, entry_start, entry_end-entry_start);
        path[entry_end-entry_start] = '\0';
        // if missing append / to end of path
        if (entry_end[-1] != '/') {
            strcat(path, "/");
        }
        // get file and dir names in that folder and add to list
        append_binaries_to_list(path, &binaries, bin_cnt_ptr, bin_lst_idx);
        // process next path
        // move pointers to start of next entry
        entry_start = entry_end;
        // if one char before first char of next entry -> move one forwad
        if (*entry_end == ':') {
            entry_start++;
        }
    }
    append_builtin_utilities_to_list(&binaries, bin_cnt_ptr, bin_lst_idx);
    return binaries;
}
