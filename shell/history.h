#ifndef HISTORY_H
#define HISTORY_H

#include <stdlib.h>
#include <string.h>

#include "string_utils.h"

extern int history_size;

extern struct history_entry* history_current;
extern struct history_entry* history_head;
extern struct history_entry* history_tail;

struct history_entry {
    char* input_string;
    struct history_entry* previous_entry;
    struct history_entry* next_entry;
};

// append string to entry
void append_string_to_history(char* input_string);

// appends the entry to the list
void append_entry_to_list(struct history_entry* entry);

// remove entry from list if exists
void remove_string_from_history(char* input_string);

// remove the specified entry from the list
void remove_entry_from_history(struct history_entry* entry);

// free a entry and its contents
void free_history_entry(struct history_entry* entry);

// resets the history index for get_next and get_previous
void reset_history_index();

// get entry containing the specified string
// if not found returns NULL
struct history_entry* get_entry_by_string(char* input_string);

// gets the histiry entry with the next higher index
char* get_next_history_entry_string();

// gets the history entry with the next lower index
char* get_previous_history_entry_string();

// gets the n-th entry from the back, starting with 0
char* get_nth_history_entry_string(int index);

// print history to console
void print_history();

#endif