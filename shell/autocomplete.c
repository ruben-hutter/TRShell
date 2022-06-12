#include "autocomplete.h"

// stores the last approach
char* last_approach = NULL;

char* autocomplete(char* approach) {
    update_last_approach(approach);
    // test: approach is single word
    if (is_single_word(approach)) {
        // complete binaries and builtins
        querry_directories(approach);
        return querry_directories(approach);
    }
    // complete directories
    return querry_binaries(approach);
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
    bool found = false;
    // split string into pre, path and pth_approach
    struct approach_split* ap_split = auto_string_manip(approach);
    // get all dir and file names at path
    int* dirs_length;
    *dirs_length = 0;
    // create list to store dir and file names
    char** name_list = malloc(DEFAULT_LENGTH * sizeof(char*));
    // current mex cap of the list
    int* name_list_length;
    *name_list_length = DEFAULT_LENGTH;
    // current insert position in the list
    int* name_list_index;
    *name_list_index = 0;
    append_names_to_list(ap_split->path, name_list, name_list_length, name_list_index);
    // compare against list
    char* match = compare_against_list(ap_split->n_complete, name_list, name_list_index);
    // on double match
    if (!match) {
        // print all matching
        print_matching_entries_from_list(name_list, name_list_index, ap_split->n_complete);
    }
    // free name list
    free_string_array(name_list, name_list_index);
    // free an approach split object
    free_approach_split(ap_split);
    return match;
}

// returns the single matching binaries if existing
// returns null on single or multiple matches
char* querry_binaries(char* approach) {
    // get list of binaries
    int* binaries_length;
    *binaries_length = 0;
    char** binaries_list = get_binaries(binaries_length);
    // compare approach against list
    char* match = compare_against_list(approach, binaries_list, binaries_length);
    // on double match
    if (!match) {
        // print all matching
        print_matching_entries_from_list(binaries_list, binaries_length, approach);
    }
    free_string_array(binaries_list, binaries_length);
    return match;
}

// returns a list of all binaries at the locations specified in PATH
char** get_binaries(int* name_list_index) {
    // create list to store dir and file names
    char** name_list = malloc(DEFAULT_LENGTH * sizeof(char*));
    // current mex cap of the list
    int* name_list_length;
    *name_list_length = DEFAULT_LENGTH;
    // current insert position in the list
    *name_list_index = 0;

    // add dir and file names to list
    // get comma seperated list of directories
    char* env_path = get_local_table_entry_value("PATH");
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
        char* path[entry_length];      
        // copy entry to path
        strncpy(path, entry_start, entry_end-entry_start);
        path[entry_end-entry_start] = '\0';
        // if missing append / to end of path
        if (entry_end[-1] != '/') {
            strcat(path, "/");
        }
        // get file and dir names in that folder and add to list
        append_names_to_list(path, name_list, name_list_length, name_list_index);
        // process next path
        // move pointers to start of next entry
        entry_start = entry_end;
        // if one char before first char of next entry -> move one forwad
        if (*entry_end == ':') {
            entry_start++;
        }
    }
    append_builtin_utilities_to_list(name_list, name_list_length, name_list_index);
    return name_list;
}

// append the names of all files at the specified path to the list
void append_names_to_list(char* path, char** name_list, int* name_list_length, int* name_list_index) {
    DIR *dir;
    struct dirent *ent;
    // open dir at path
    if ((dir = opendir (path)) != NULL) {
        // append all file and directory names to list
        while ((ent = readdir (dir)) != NULL) {
            // expand buffer if necessary
            if (name_list_index >= name_list_length) {
                char** new_list = realloc(name_list, 2 * (*name_list_length) * sizeof(char*));
                if (!new_list) {
                    free_string_array(name_list, name_list_index);
                    return;
                }
                name_list = new_list;
                *name_list_length *= 2;
            }
            // append new element
            name_list[(*name_list_index)++] = get_malloced_copy(ent->d_name);
        }
        closedir (dir);
    } else {
        return;
    }
}

// appends the naems of all builtin utilities to the list
void append_builtin_utilities_to_list(char** name_list, int* name_list_length, int* name_list_index) {
    // iterate over builtin utilities
    for (int idx = 0; idx < builtin_utility_count; idx++) {
        // expand buffer if necessary
        if (name_list_index >= name_list_length) {
            char** new_list = realloc(name_list, 2 * (*name_list_length) * sizeof(char*));
            if (!new_list) {
                free_string_array(name_list, name_list_index);
                return;
            }
            name_list = new_list;
            *name_list_length *= 2;
        }
        // append new element
        name_list[(*name_list_index)++] = get_malloced_copy(builtin_utilities[idx].name);
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

// prints all entries of a list in a ls like fashion to the std out
void print_matching_entries_from_list(char** entry_list, int list_length, char* approach) {
    // group entries to lines
    // print all lines
}

// manipulates the given string for autocompletion [autocomplete]
struct approach_split* auto_string_manip(char* string) {
    // struct ptr to return
    struct approach_split* app_split;
    // members to bind to struct
    char* m_pre;
    char* m_path;
    char* m_n_complete;
    // delimiters
    char slash = '/';
    char space = ' ';

    // get pre
    char* pre = strchar(string, space);
    m_pre = get_malloced_copy(pre);

    // get n_complete
    char* n_complete = strrchr(string, slash);
    if (!n_complete) {
        // path not partially given
        // take rest after command
        n_complete = strrchr(string, space);
        // remove double-quotes & backslashes
        // put between single-quotes
        m_n_complete = get_malloced_copy(n_complete);
    }

    // get path
    char* path = strtok(NULL, delimiter);
    if (path) {
        m_path = get_malloced_copy(path);
    }

    // bind everything to struct
    app_split->pre = pre;
    app_split->path = path;
    app_split->n_complete = n_complete;

    if (strchr(string, slash)) {
        // already entered a part of path
        // take only last part of given path
        crop_string_to_end(string, slash);
        // tokenize string
        char* tok = strtok(string, delimiter);
        while (tok != NULL) {
            tok_concat(tok);
            pch = strtok (NULL, " ,.-");
        }
    } else {
        // only command and a part of a word is given
    }
    printf("string after crop: %s\n", string);
}

// frees an apprach split struct with all its members
void free_approach_split(struct approach_split* ap_split) {
    if (ap_split->pre) {
        free(ap_split->pre);
    }
    if (ap_split->path) {
        free(ap_split->path);
    }
    if (ap_split->n_complete) {
        free(ap_split->n_complete);
    }
    free(ap_split);
}

/* returns the history entry with the best match
char* querry_history(char* approach) {
    char* current_entry = NULL;
    int appr_length = strlen(approach);
    char* best_entry = NULL;

    // if first letter not match -> ignore
    reset_history_index();
    while (!is_at_head()) {
        current_entry = get_previous_history_entry_string();
        // if not matching lengths -> ignore
        if (strlen(approach) > strlen(current_entry)) {
            continue;
        }

        // start comparing
        int curr_match_length = 0;
        while ((curr_match_length <= appr_length) && (approach[curr_match_length] == current_entry[curr_match_length])) {
            curr_match_length++;
        }
        
        // if new best update best
        if (curr_match_length > hist_rating) {
            hist_rating = curr_match_length;
            if (best_entry) {
                free(best_entry);
            }
            best_entry = get_malloced_copy(current_entry);
            cut_at_trailing_newline(best_entry);
        }
    }
    return best_entry;
}
*/