#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>

#include "command_tree.h"

#define HASH_TABLE_INIT_SIZE 256
#define MAX_STACK_SIZE 256

#define FLAG_EXPORT (1 << 0)

extern const uint32_t hash_function_prime;
extern const uint32_t hash_function_seed;

struct symbol_table_stack {
    int table_count;
    struct symbol_table* local_table;
    struct symbol_table* global_table;
    struct symbol_table* table_list[MAX_STACK_SIZE];
};

struct symbol_table {
    int stack_level;
    int cell_count;
    int used_cell_count;
    struct symbol_table_entry** entries;
};

enum entry_type {
    STRING_ENTRY,
    FUNCTION_ENTRY
};

struct symbol_table_entry {
    char* name;
    enum entry_type value_type;
    char* value;
    unsigned int flags;
    struct symbol_table_entry* next;
    struct tree_node* function_body;
};

// hashing function
uint32_t fnva1a(char* string, uint32_t hash);

// get the cell in the entry array depending of the strings hash value
int get_cell(struct symbol_table *table, char* string);

// allocates a new hash table and returns a pointer to it
struct symbol_table* get_allocated_table(void);

// initialize a new symbol table
void init_table(void);

// returns an allocated symbol table on the passed stack level
struct symbol_table* get_new_table_on_level(int level);

// pushes the passed table to the top of the stack
// the pushed table becomes thereby becomes the local table
void stack_push(struct symbol_table* table);

// allocates a new table and pushes it ontop of the stack
struct symbol_table* get_new_table_on_stack(void);

// pop the topmost table from the stack
struct symbol_table* stack_pop(void);

// free all memory allocated for a symbol table
void free_table(struct symbol_table* table);

// free all tables on table stack
void free_table_stack(void);

// creates an entry for the passed sting and adds it to the specified table
struct symbol_table_entry* add_to_specific_table(char* string,
                                                    struct symbol_table* table);

// remove entry from the table
int remove_from_specific_table(struct symbol_table_entry* entry,
                                struct symbol_table* table);
    
// removes the first (and theoretically last) occurence
// of that entry from the corresponding table
void remove_from_table(struct symbol_table_entry* entry);

// look for a symbol in a table
struct symbol_table_entry* lookup_symbol(char* string,
                                            struct symbol_table* table);

// add a string to a table
struct symbol_table_entry* add_to_table(char* string);

// lookup a symbol in the local table
struct symbol_table_entry* get_local_table_entry(char* string);

// returns the value of the entry with that name if exists
char* get_local_table_entry_value(char* entry_name);

// lookup a symbol in all tables of the table stack
struct symbol_table_entry* get_table_entry(char* string);

// get pointer to local table
struct symbol_table* get_local_table(void);

// get pointer tp the global table
struct symbol_table* get_global_table(void);

// get pointer to the table stack
struct symbol_table_stack* get_table_stack(void);

// set the value of a specific entry
void set_entry_value(struct symbol_table_entry* entry, char* new_value);

// prints the local table to the stdout
void print_local_table(void);

#endif
