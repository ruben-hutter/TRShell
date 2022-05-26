#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>

#include "command_tree.h"

#define HASH_TABLE_INIT_SIZE 256
#define MAX_STACK_SIZE 256

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
    struct tree_node *function_body;
};

#endif
