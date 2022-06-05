#include "cd.h"
#include "../string_utils.h"
#include <errno.h>

errno;

void cd(int argc, char** argv) {
    int dest_len;
    if (argc < 2) {
        // cd without arguments -> go HOME
        chdir(get_local_table_entry_value("HOME"));
    } else {
        char* dest = *(argv+1);
        if (strcmp(dest, "..")) {
            dest_len = 0;
        } else {
            dest_len = strlen(dest);
        }
        chdir(dest);
    }
    // update pwd
    update_pwd(dest_len);
}

void update_pwd(int dest_len) {
    struct symbol_table_entry *entry = get_local_table_entry("PWD");
    int new_path_len = strlen(entry->value) + dest_len;
    char* cwd = get_malloced_empty_string(new_path_len);
    getcwd(cwd, new_path_len * sizeof(cwd));
    set_entry_value(entry, cwd);
    free(cwd);
}