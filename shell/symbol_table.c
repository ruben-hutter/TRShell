#include <symbol_table.h>

struct symbol_table_stack table_stack;
int stack_level;

extern const uint32_t hash_function_prime;
extern const uint32_t hash_function_seed;
extern uint32_t get_hash_of_byte(unsigned char byte, uint32_t hash);
extern uint32_t get_hash(char** string, uint32_t hash);

// get the cell in the entry array depending of the strings hash value
get_cell(struct symbol_table *table, char* string) {
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
        Ifree(table);
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
                    free_malloced_string(current_entry->name);
                }

                if (current_entry->value) {
                    free_malloced_string(current_entry->value);
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
struct symbol_table_entry* add_to_table(char* string, struct symbol_table* table) {

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

