#include "cd.h"

void cd(int argc, char** argv) {
    char* dest_path;
    int changed_dir;

    errno = 0;

    if (argc < 2) {
        // cd without arguments -> go HOME
        dest_path = get_local_table_entry_value("HOME");
        changed_dir = chdir(dest_path);
    } else {
        // cd with a PATH
        dest_path = *(argv+1);
        changed_dir = chdir(dest_path);
    }
    if (changed_dir == 0) {
        // update pwd
        update_pwd();
    } else {
        // print the error message
        perror("Error changing directory");
    }
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
