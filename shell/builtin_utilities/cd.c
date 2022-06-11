#include "cd.h"
#include "../string_utils.h"

void cd(int argc, char** argv) {
    char* dest_path;

    if (argc < 2) {
        // cd without arguments -> go HOME
        dest_path = get_local_table_entry_value("HOME");
        chdir(dest_path);
    } else {
        // cd with a PATH
        dest_path = *(argv+1);
        if (strchr(dest_path, ' ')) {
            // destination contains spaces
            printf("has space\n");
            // prepend them with backslash
        }
        chdir(dest_path);
    }
    // update pwd
    update_pwd();
}

// updates the pwd in the symbol table
void update_pwd() {
    char buff[1024];
    int dest_len;

    struct symbol_table_entry *entry = get_local_table_entry("PWD");
    // get actual path
    getcwd(buff, sizeof(buff));
    dest_len = strlen(buff);
    // create actual path on heap
    char* cwd = get_malloced_empty_string(dest_len);
    strcpy(cwd, buff);
    // set actual path value in symbol table
    set_entry_value(entry, cwd);
    free(cwd);
}
