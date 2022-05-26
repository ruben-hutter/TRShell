#include "init.h"

// add all environment variables to the symbol table
void init_shell() {
    // init symbol table
    init_table();

    struct symbol_table_entry* entry;
    char **p2 = environ;
    
    while(*p2) {
        char *eq = strchr(*p2, '=');
        if (eq) {
            int len = eq-(*p2);
            char name[len + 1];
            strncpy(name, *p2, len);
            name[len] = '\0';
            entry = add_to_table(name);

            if (entry) {
                set_entry_value(entry, eq + 1);
                entry->flags |= FLAG_EXPORT;
            }
        } else {
            entry = add_to_table(*p2);
        }
        p2++;
    }
    
    entry = add_to_table("PS1");
    set_entry_value(entry, "$ ");
    
    entry = add_to_table("PS2");
    set_entry_value(entry, "> ");
    
}