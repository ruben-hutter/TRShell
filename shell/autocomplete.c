#include "autocomplete.h"

// stores the last approach
char* last_approach = NULL;

char* autocomplete(char* approach) {
    update_last_approach(approach);
    // test: approach is empty string
    if (is_only_whitespace(approach)) {
        return NULL;
    }
    // check if approach is history querry
    if (is_history_querry(approach)) {
        return querry_history(approach);
    }
    // test: approach is single word
    if (is_single_word(approach)) {
        // complete binaries and builtins
        return querry_binaries(approach);
    }
    // complete directories
    return querry_directories(approach);
}

// returns 1 if the approach is a history querry
int is_history_querry(char* approach) {
    if (approach[0] == '?' && strlen(approach) > 1) {
        return 1;
    }
    return 0;
}

// updates the last_approach with a malloced copy of the current one
void update_last_approach(char* approach) {
    // free old approach
    if (last_approach) {
        free(last_approach);
    }
    last_approach = get_malloced_copy(approach);
}

// returns the single matching directories if existing
// returns null on single or multiple matches
char* querry_directories(char* approach) {
    int no_path = false;
    // split string into pre, path and pth_approach
    struct approach_split* ap_split = auto_string_manip(approach);
    // set path in case of null
    if (!ap_split) {
        return NULL;
    }
    if (!ap_split->path) {
        no_path = true;
        ap_split->path = get_current_working_path();
    }
    // create list to store dir and file names
    char** dirs = (char**) malloc(DEFAULT_LENGTH * sizeof(char*));
    // current mex cap of the list
    int dirs_len = DEFAULT_LENGTH;
    int* dirs_len_ptr = &dirs_len;
    // current insert position in the list
    int dirs_idx = 0;
    int* dirs_idx_ptr = &dirs_idx;
    if (
        (strcmp(ap_split->pre, "cd ") != 0)
        && (strcmp(ap_split->pre, "ls ") != 0)
    ) {
        append_files_to_list(ap_split->path, &dirs, dirs_len_ptr, dirs_idx_ptr);
    }
    append_dirs_to_list(ap_split->path, &dirs, dirs_len_ptr, dirs_idx_ptr);
    // compare against list

    char* match = compare_against_list(ap_split->n_complete, dirs, dirs_idx);
    // free name list
    free_string_arr(dirs, dirs_idx);
    // handle no match
    if (!match) {
        // free an approach split object
        free_approach_split(ap_split);
        return NULL;
    }
    // insert backslash before whitespace
    char* esc_match = insert_char_before_char(match, ' ', '\\');
    if (!esc_match) {
        free(match);
        free_approach_split(ap_split);
        return NULL;
    }

    free(match);
    char* input = NULL;
    // reconstruct input
    if (no_path) {
        int ipt_len = get_concatenated_length(2, ap_split->pre, esc_match);
        input = get_malloced_empty_string(ipt_len);
        concatenate(2, input, ap_split->pre, esc_match);
    } else {
        int ipt_len = get_concatenated_length(3, ap_split->pre, ap_split->esc_path, esc_match);
        input = get_malloced_empty_string(ipt_len);
        concatenate(3, input, ap_split->pre, ap_split->esc_path, esc_match);
    }
    // free an approach split object
    free_approach_split(ap_split);
    free(esc_match);
    return input;
}

// append the names of all files at the specified path to the list
void append_files_to_list(char* path, char*** list_ptr, int* list_len_ptr,
                            int* list_idx_ptr) {
    DIR *dir;
    struct dirent *entry;
    // open dir at path
    if ((dir = opendir(path)) != NULL) {
        // append all file and directory names to list
        while ((entry = readdir(dir)) != NULL) {
            // ignore . link
            if (strcmp(".", entry->d_name) == 0) {
                continue;
            }
            // ignore .. link
            if (strcmp("..", entry->d_name) == 0) {
                continue;
            }
            // get file information
            struct stat entry_info;
            // get abs path of file
            char* abs_path = concat_name_to_path(path, entry->d_name);
            // handle inaccessible file info
            if (stat(abs_path, &entry_info) == -1) {
                continue;
            }
            // ignore directories and files that are not executable
            if (S_ISDIR(entry_info.st_mode)) {
                continue;
            }
            free(abs_path);
            // expand buffer if necessary
            if (*list_idx_ptr >= *list_len_ptr) {
                char** new_list = (char**) realloc(*list_ptr,
                    2 * (*list_len_ptr) * sizeof(char*));
                if (!new_list) {
                    free_string_arr(*list_ptr, *list_idx_ptr);
                    return;
                }
                *list_ptr = new_list;
                (*list_len_ptr) *= 2;
            }
            // append new element
            (*list_ptr)[(*list_idx_ptr)++] = get_malloced_copy(entry->d_name);
        }
        closedir(dir);
    }
}

// append the names of all directories at the specified path to the list
void append_dirs_to_list(char* path, char*** list_ptr, int* list_len_ptr,
                            int* list_idx_ptr) {
    DIR *dir;
    struct dirent *entry;
    // open dir at path
    if ((dir = opendir(path)) != NULL) {
        // append all file and directory names to list
        while ((entry = readdir(dir)) != NULL) {
            // ignore . link
            if (strcmp(".", entry->d_name) == 0) {
                continue;
            }
            // ignore .. link
            if (strcmp("..", entry->d_name) == 0) {
                continue;
            }
            // get file information
            struct stat entry_info;
            // get abs path of file
            char* abs_path = concat_name_to_path(path, entry->d_name);
            // handle inaccessible file info
            if (stat(abs_path, &entry_info) == -1) {
                continue;
            }
            // ignore directories and files that are not executable
            if (!S_ISDIR(entry_info.st_mode)) {
                continue;
            }
            free(abs_path);
            // expand buffer if necessary
            if (*list_idx_ptr >= *list_len_ptr) {
                char** new_list = (char**) realloc(*list_ptr,
                    2 * (*list_len_ptr) * sizeof(char*));
                if (!new_list) {
                    free_string_arr(*list_ptr, *list_idx_ptr);
                    return;
                }
                *list_ptr = new_list;
                (*list_len_ptr) *= 2;
            }
            // append new element
            (*list_ptr)[(*list_idx_ptr)++] = get_malloced_copy_w_char(entry->d_name, '/');
        }
        closedir(dir);
    }
}

// returns the single matching binaries if existing
// returns null on single or multiple matches
char* querry_binaries(char* approach) {
    // get list of binaries
    int bin_len = 0;
    int* binaries_length = &bin_len;
    // get list of all binaries including builtins
    char** binaries_list = get_binaries(binaries_length);
    // compare approach against list
    char* match = compare_against_list(approach, binaries_list, *binaries_length);
    free_string_arr(binaries_list, *binaries_length);
    return match;
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
    // single entry of local table path
    char* entry = strtok(env_path, delimiter);
    int entry_len = 0;
    while (entry != NULL) {
        entry_len = strlen(entry);
        // path of entry with space for terminating slash
        char path[entry_len + 2];
        // copy entry, slash and terminator into path
        strcpy(path, entry);
        path[entry_len] = '/';
        path[entry_len + 1] = '\0';
        // get file and dir names in that folder and add to list
        append_binaries_to_list(path, &binaries, bin_cnt_ptr, bin_lst_idx);
        entry = strtok(NULL, delimiter);
    }
    append_builtin_utilities_to_list(&binaries, bin_cnt_ptr, bin_lst_idx);
    return binaries;
}

// append the names of all executable files at the specified path to the list
void append_binaries_to_list(char* path, char*** list_ptr, int* list_len_ptr,
                            int* list_idx_ptr) {
    DIR *dir;
    struct dirent *entry;
    // open dir at path
    if ((dir = opendir(path)) != NULL) {
        // append all file and directory names to list
        while ((entry = readdir(dir)) != NULL) {
            // ignore . link
            if (strcmp(".", entry->d_name) == 0) {
                continue;
            }
            // ignore .. link
            if (strcmp("..", entry->d_name) == 0) {
                continue;
            }
            // get file information
            struct stat entry_info;
            // get abs path of file
            char* abs_path = concat_name_to_path(path, entry->d_name);
            // handle inaccessible file info
            if (stat(abs_path, &entry_info) == -1) {
                continue;
            }
            // ignore directories and files that are not executable
            if (!is_executable_file(&entry_info)) {
                continue;
            }
            free(abs_path);
            // expand buffer if necessary
            if (*list_idx_ptr >= *list_len_ptr) {
                char** new_list = (char**) realloc(*list_ptr,
                    2 * (*list_len_ptr) * sizeof(char*));
                if (!new_list) {
                    free_string_arr(*list_ptr, *list_idx_ptr);
                    return;
                }
                *list_ptr = new_list;
                (*list_len_ptr) *= 2;
            }
            // append new element
            (*list_ptr)[(*list_idx_ptr)++] = get_malloced_copy(entry->d_name);
        }
        closedir(dir);
    }
}

// appends the naems of all builtin utilities to the list
void append_builtin_utilities_to_list(char*** list_ptr, int* list_len_ptr, int* list_idx_ptr) {
    // iterate over builtin utilities
    for (int idx = 0; idx < builtin_utility_count; idx++) {
        // expand buffer if necessary
        if (*list_idx_ptr >= *list_len_ptr) {
            char** new_list = (char**) realloc(*list_ptr, 2 * (*list_len_ptr) * sizeof(char*));
            if (!new_list) {
                free_string_arr(*list_ptr, *list_idx_ptr);
                return;
            }
            *list_ptr = new_list;
            (*list_len_ptr) *= 2;
        }
        // append new element
        (*list_ptr)[(*list_idx_ptr)++] = get_malloced_copy(builtin_utilities[idx].name);
    }
}


// prints all entries of a list in a ls like fashion to the std out
void print_matching_entries_from_list(char** entry_list, int list_length, char* approach) {
    // init formatting
    int format_index = 0;
    char format[3] = {' ', ' ', '\n'};
    printf("\n");
    for (int idx = 0; idx < list_length; idx++) {
        // ignore irrelevant results
        if (!string_starts_with(entry_list[idx], approach)) {
            continue;
        }
        // parint result
        printf("%-26s%c", entry_list[idx], format[format_index % 3]);
        format_index++;
    }
    // print newline if no already happened above
    if (format_index % 3 != 0) {
        printf("\n");
    } 
}

// manipulates the given string for autocompletion
struct approach_split* auto_string_manip(char* string) {
    // struct ptr to return
    struct approach_split* app_split = (struct approach_split*)
        malloc(sizeof(struct approach_split));
    // members to bind to struct
    char* m_pre = NULL;
    char* m_path = NULL;
    char* m_esc_path = NULL;
    char* m_n_complete = NULL;
    // delimiters
    char slash = '/';
    char space = ' ';
    // input length
    int string_len = strlen(string);

    // get pre
    char* pre = strchr(string, space);
    unsigned int pre_len = pre - string + 1;
    m_pre = get_malloced_empty_string(pre_len);
    strncpy(m_pre, string, pre_len);

    // get n_complete
    char* n_complete = strrchr(string, slash);
    if (!n_complete) {
        // path not partially given
        // take rest after command
        unsigned int n_complete_len = string_len - pre_len;
        m_n_complete = get_malloced_empty_string(n_complete_len);
        strncpy(m_n_complete, pre + 1, n_complete_len);
        // format n_complete
        remove_back_n_quotes(&m_n_complete);
        // bind everything to struct
        app_split->pre = m_pre;
        app_split->path = m_path;
        app_split->esc_path = m_esc_path;
        app_split->n_complete = m_n_complete;
        return app_split;
    }
    unsigned int n_complete_len = (string + string_len) - n_complete - 1;
    m_n_complete = get_malloced_empty_string(n_complete_len);
    strncpy(m_n_complete, n_complete + 1, n_complete_len);
    // format n_complete
    remove_back_n_quotes(&m_n_complete);

    // get esc_path
    unsigned int esc_path_len = string_len - pre_len - n_complete_len;
    m_esc_path = get_malloced_empty_string(esc_path_len);
    strncpy(m_esc_path, pre + 1, esc_path_len);

    // get path
    int quotes_count = count_char_in_word(m_esc_path, '"');
    int backslash_count = count_char_in_word(m_esc_path, '\\');
    unsigned int path_len = esc_path_len - quotes_count - backslash_count;
    m_path = get_malloced_copy(m_esc_path);
    remove_back_n_quotes(&m_path);

    // bind everything to struct
    app_split->pre = m_pre;
    app_split->path = m_path;
    app_split->esc_path = m_esc_path;
    app_split->n_complete = m_n_complete;

    return app_split;
}

// remove backslashes and quotes
void remove_back_n_quotes(char** string) {
    char* back_n_quotes = "\\\"";
    // remove double-quotes & backslashes
    remove_chars_from_string(*string, back_n_quotes);
}

// frees an apprach split struct with all its members
void free_approach_split(struct approach_split* ap_split) {
    if (!ap_split) {
        return;
    }
    if (ap_split->pre) {
        free(ap_split->pre);
    }
    if (ap_split->path) {
        free(ap_split->path);
    }
    if (ap_split->esc_path) {
        free(ap_split->esc_path);
    }
    if (ap_split->n_complete) {
        free(ap_split->n_complete);
    }
    free(ap_split);
}

// returns the first match to the approach
// if no match found, NULL is returned 
char* querry_history(char* raw_approach) {
    int r_apr_len = strlen(raw_approach);
    // new array for approach without leading ?
    char approach[r_apr_len - 1];
    // copy section without "? "
    strncpy(approach, raw_approach + 2, r_apr_len - 2);
    terminate_string_at(approach, r_apr_len - 2);
    // compare approach with history
    char* curr_string = get_previous_history_entry_string();
    char* match = NULL;
    reset_history_index();
    // iterate over history
    for (int idx = 0; idx < history_size; idx++) {
        // if not matching -> continue
        if (!string_starts_with(curr_string, approach)) {
            curr_string = get_previous_history_entry_string();
            continue;
        }
        // return match
        match = get_malloced_copy(curr_string);
        // remove newline
        cut_at_trailing_newline(match);
        return match;
    }
    return NULL;
}

// searches the list for a unique possible match of the approach and returns the match
// if no match NULL is returned
char* compare_against_list(char* approach, char** entry_list, int list_length) {
    int approach_length = strlen(approach);
    int found = false;
    char* match = NULL;
    // iterate over lsit to find matches
    for (int index = 0; index < list_length; index++) {
        // if not matching -> continue
        if (!string_starts_with(entry_list[index], approach)) {
            continue;
        }
        // if match was previously found -> return NULL as match is not unique
        if (found) {
            print_matching_entries_from_list(entry_list, list_length, approach);
            dump_buffer();
            return NULL;
        }
        found = true;
        match = get_malloced_copy(entry_list[index]);
    }
    return match;
}

// concatenates path with filename
char* concat_name_to_path(char* path, char* name) {
    int len = get_concatenated_length(2, path, name);
    char* concat_string = get_malloced_empty_string(len);
    concatenate(2, concat_string, path, name);
    return concat_string;
}

// checks if a file is executable
int is_executable_file(struct stat* entry_info) {
    return (
        !S_ISDIR(entry_info->st_mode)
        && (
            (entry_info->st_mode & S_IXUSR)
            || (entry_info->st_mode & S_IXGRP)
            || (entry_info->st_mode & S_IXOTH)
        )
    );
}
