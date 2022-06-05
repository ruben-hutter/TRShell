#include "cd.h"
#include "../string_utils.h"

void cd(int argc, char** argv) {
    if (argc < 2) {
        // cd without arguments -> go HOME
        chdir(get_local_table_entry_value("HOME"));
    } else {
        chdir(*(argv+1));
    }
    // update pwd
    update_pwd();
}

void update_pwd() {
    char* cwd = get_malloced_empty_string(50);
    struct symbol_table_entry *entry = get_local_table_entry("PWD");
    getcwd(cwd, 50);
    set_entry_value(entry, cwd);
}