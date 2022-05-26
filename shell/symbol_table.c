#include "symbol_table.h"

const uint32_t hash_function_prime = 0x01000193;
const uint32_t hash_function_seed = 0x811C9DC5;

struct symbol_table_stack table_stack;
int stack_level;

uint32_t fnva1a(char* string, uint32_t hash) {
    if (!string) {
        return 0;
    }

    unsigned char *p = (unsigned char*) string;
    while (*p) {
        hash = (*p++ ^ hash) * hash_function_prime;
    }
    return hash;
}

// get the cell in the entry array depending of the strings hash value
int get_cell(struct symbol_table *table, char* string) {
    // nullpinter -> return
    if (!table) {
        return 0;
    }
    // nullpointer -> return
    if (!string) {
        return 0;
    }
    // hash string and calc cell
    return fnva1a(string, hash_function_seed) % table->cell_count;
}

// allocates a new hash table and returns a pointer to it
struct symbol_table* get_allocated_table() {
    // alloc space for new table
    struct symbol_table *table = malloc(sizeof(struct symbol_table));

    // null pointer -> exit
    if (!table) {
        free(table);
        fprintf(stderr, "fatal error: symbol table allocation failed");
    }

    // set init values
    table->cell_count = HASH_TABLE_INIT_SIZE;
    table->used_cell_count = 0;

    // allocate space for entries
    size_t entries_size = sizeof(struct table_entry*) * HASH_TABLE_INIT_SIZE;
    table->entries = malloc(entries_size);
    if (!table->entries) {
        free(table);
        fprintf(stderr, "fatal error: symbol table allocation failed");
    }

    // erase memory for entries
    memset(table->entries, 0, entries_size);
    return table;
}

// initialize a new symbol table
void init_table() {
    struct symbol_table* table = get_allocated_table();
    table->stack_level = 0;
    stack_level = 0;

    table_stack.table_count = 1;
    table_stack.global_table = table;
    table_stack.local_table = table;
    table_stack.table_list[0] = table;
}

// returns an allocated symbol table on the passed stack level
struct symbol_table* get_new_table_on_level(int level) {
    struct symbol_table* table = get_allocated_table();
    table->stack_level = level;
    return table;
}

// pushes the passed table to the top of the stack. The pushed table becomes thereby becomes the local table
void stack_push(struct symbol_table* table) {
    table_stack.table_list[table_stack.table_count] = table;
    table_stack.table_count++;
    table_stack.local_table = table;
}

// allocates a new table and pushes it ontop of the stack
struct symbol_table* get_new_table_on_stack() {
    struct symbol_table* table = get_new_table_on_level(++stack_level);
    stack_push(table);
    return table;
}

// pop the topmost table from the stack
struct symbol_table* stack_pop() {
    // empty stack -> return NULL
    if ( table_stack.table_count == 0) {
        return NULL;
    }

    // get table from stack
    struct symbol_table* table = table_stack.table_list[table_stack.table_count - 1];
    table_stack.table_count--;
    table_stack.table_list[table_stack.table_count];
    stack_level--;

    // if stack empty -> adjust pointers and return
    if (table_stack.table_count == 0) {
        table_stack.local_table = NULL;
        table_stack.global_table = NULL;
        return table;
    }

    // set next lower table as local table
    table_stack.local_table = table_stack.table_list[table_stack.table_count - 1];
    return table;
}

// free all memory allocated for a symbol table
void free_table(struct symbol_table* table) {
    // passed null pointer
    if (!table) {
        return;
    }

    // tables entry pointer is null
    if (!table->entries){
        return;
    }

    // if there are used cells in table -> free
    if (table->used_cell_count > 0) {
        struct symbol_table_entry** cell_iterator = table->entries;
        struct symbol_table_entry** last_cell = table->entries + table->cell_count;
        // iterate over cell
        while(cell_iterator < last_cell) {
            // iterate through all elements attatched to the current cell
            struct symbol_table_entry* current_entry = *cell_iterator;
            struct symbol_table_entry* next_entry = NULL;
            while(current_entry) {
                next_entry = current_entry->next;

                if (current_entry->name) {
                    free(current_entry->name);
                }

                if (current_entry->value) {
                    free(current_entry->value);
                }

                if (current_entry->function_body) {
                    free_tree_from_root(current_entry->function_body);
                }
                free(current_entry);
                current_entry = next_entry;
            }
            // increase iterator
            cell_iterator++;
        }
    }

    free(table->entries);
    free(table);
}

// creates an entry for the passed sting and adds it to the specified table
struct symbol_table_entry* add_to_specific_table(char* string, struct symbol_table* table) {

    // table pinter is NULL
    if (!table) {
        return NULL;
    }

    // alloc space for the new entry
    struct symbol_table_entry* entry = malloc(sizeof(struct symbol_table_entry));
    if (!entry) {
        fprintf(stderr, "fatal error: symbol table entry allocation failed");
    }
    memset(entry, 0, sizeof(struct symbol_table_entry));
    
    // copy string to entries text field
    entry->name = get_malloced_empty_string(strlen(string));
    strcpy(entry->name, string);

    // prepend entry to hash maps linked list for the resulting hash
    // get cell index
    int cell = get_cell(table, string);
    // append list to new entry
    entry->next = table->entries[cell];
    // set new entry as first element in that cell
    table->entries[cell] = entry;
    // increase cell count
    table->used_cell_count++;
    return entry;
}

// remove entry from the table
int remove_from_specific_table(struct symbol_table_entry* entry, struct symbol_table* table) {
    // get head of entry list appended to that cell
    int cell = get_cell(table, entry->name);
    struct symbol_table_entry* iterator = table->entries[cell];
    struct symbol_table_entry* temp = NULL;

    // iterate thourgh list and find our target
    while(iterator) {

        // entry found
        if(iterator == entry) {
            // remove from linked list
            if (!temp) {
                // entry is head
                table->entries[cell] = iterator->next;
            } else {
                // entry found in list
                temp->next = iterator->next;
            }

            // free memory
            if (entry->value) {
                free(entry->value);
            }
            if (entry->function_body) {
                free_tree_from_root(entry->function_body);
            }
            free(entry->name);
            free(entry);
            table->used_cell_count--;
            return 1;
        }

        // iterate to next element in list
        temp = iterator;
        iterator = iterator->next;
    }
}
    
// removes the first (and theoretically last) occurence of that entry from the corresponding table
void remove_from_table(struct symbol_table_entry* entry) {
    int index = table_stack.table_count - 1;
    do {
        if (remove_from_specific_table(entry, table_stack.table_list[index])) {
            return;
        }
        index--;
    } while(index >= 0);
}

struct symbol_table_entry* lookup_symbol(char* string, struct symbol_table* table) {
    // check stringpointer null
    if (!string) {
        return NULL;
    }

    // check table pointer null
    if (!table) {
        return NULL;
    }

    // get cell index
    int cell = get_cell(table, string);

    // get head of list attatched to this cell
    struct symbol_table_entry* iterator = table->entries[cell];

    // iterate though list to find entry
    while(iterator) {
        if (strcmp(iterator->name, string) == 0){
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

// add a string to a table
struct symbol_table_entry* add_to_table(char* string) {
    
    // check nullpointer
    if (!string) {
        return NULL;
    }
    
    // check empty string
    if (*string == '\0') {
        return NULL;
    }
    
    // get local table
    struct symbol_table* table = table_stack.local_table;

    // check if entry already added (must be unique cause hashmap)
    struct symbol_table_entry* entry = lookup_symbol(string, table);
    if(entry) {
        return entry;
    }

    // add entry to table
    entry = add_to_specific_table(string, table);

    return entry;
}

// lookup a symbol in the local table
struct symbol_table_entry* get_local_table_entry(char* string) {
    return lookup_symbol(string, table_stack.local_table);
}

// lookup a symbol in all tables of the table stack
struct symbol_table_entry* get_table_entry(char* string) {
    int iterator = table_stack.table_count - 1;
    do {
        // get table with that index form stack
        struct symbol_table* current_table = table_stack.table_list[iterator];
        // lookup entry in that table
        struct symbol_table_entry* entry = lookup_symbol(string, current_table);
        // if found return
        if (entry) {
            return entry;
        }

        // go th next higher table
        iterator--;
    } while (iterator >= 0);
}

// get pointer to local table
struct symbol_table* get_local_table() {
    return table_stack.local_table;
}

// get pointer tp the global table
struct symbol_table* get_global_table() {
    return table_stack.global_table;
}

// get pointer to the table stack
struct symbol_table_stack* get_table_stack() {
    return &table_stack;
}

// set the value of a specific entry
void set_entry_value(struct symbol_table_entry* entry, char* new_value) {
    // get old value of entry
    char* old_value = entry->value;

    // check new value for null
    if (!new_value) {
        entry->value = NULL;
    } else {
        entry->value = get_malloced_empty_string(strlen(new_value));
        if (!entry->value) {
            fprintf(stderr, "fatal error: symbol table entry value allocation failed");
        } else {
            strcpy(entry->value, new_value);
        }
    }

    free(old_value);
}

// prints the local table to the stdout
void print_local_table() {
    // get local table
    struct symbol_table* table = table_stack.local_table;
    int index = 0;

    //get stack level dependant indenting
    int indent = table->stack_level << 2;

    // print header for table
    fprintf(stderr, "%*sSymbol table [Level %d];\n]", indent, " ", table->stack_level);
    fprintf(stderr, "*s===========================\n", indent, " ");
    fprintf(stderr, "*s  No               Symbol                    Val\n", indent, " ");
    fprintf(stderr, "*s------ -------------------------------- ------------\n", indent, " ");

    // iterate though entries of table if not empty
    if (table->used_cell_count > 0) {
        struct symbol_table_entry** iterator = table->entries;
        struct symbol_table_entry** last_cell = table->entries + table->cell_count;

        // iterate over cells
        while (iterator < last_cell) {
            struct symbol_table_entry* current_entry = *iterator;

            // itereate over entries in list attatched to each cell
            while(current_entry) {
                index++;
                fprintf(stderr, "%*s[%04d] %-32s '%s'\n", indent, " ", index, current_entry->name, current_entry->value);
                current_entry = current_entry->next;
            }
            iterator++;
        }
    }
}
