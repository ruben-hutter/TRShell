#include "history.h"

int history_size = 0;

struct history_entry* history_current = NULL;
struct history_entry* history_head = NULL;
struct history_entry* history_tail = NULL;

// append string to entry
void append_string_to_history(char* input_string){
    // input string is null
    if (!input_string) {
        return;
    }
    if (is_only_whitespace(input_string)) {
        return;
    }
    // malloc new node
    struct history_entry* new_entry = (struct history_entry*)malloc(sizeof(struct history_entry*));
    // add data
    new_entry->input_string = input_string;
    // remove previous occurence
    remove_string_from_history(input_string);
    // append node to list
    append_entry_to_list(new_entry);
    // increment size
    history_size++;
    // reset history index
    reset_history_index();
}

// appends the entry to the list
void append_entry_to_list(struct history_entry* entry) {
    // check for entry null
    if (!entry) {
        return;
    }
    // no next entry as this entry is the last one
    entry->next_entry = NULL;
    // previous entry will be the current lst one
    entry->previous_entry = history_tail;
    // update link current las element to new one
    if (history_tail) {
        history_tail->next_entry = entry;
    }
    // update tail pointer
    history_tail = entry;
}

// remove entry from list if exists
void remove_string_from_history(char* input_string) {
    // list empty
    if (history_size == 0) {
        return;
    }
    // check input_string null
    if (!input_string) {
        return;
    }
    // get node with specified string
    struct history_entry* entry = get_entry_by_string(input_string);
    // remove node from list
    remove_entry_from_history(entry);
    // update size
    history_size--;
}

// remove the specified entry from the list
void remove_entry_from_history(struct history_entry* entry) {
    // list empty
    if (history_size == 0) {
        return;
    }
    // check for entry null
    if (!entry) {
        return;
    }
    // if entry is head
    if (entry == history_head){
        history_head = entry->next_entry;
    }
    // update next node if appliccable
    if (entry->next_entry) {
        entry->next_entry->previous_entry = entry->previous_entry;
    }
    // update previous node if applicable
    if (entry->previous_entry) {
        entry->previous_entry->next_entry = entry->next_entry;
    }
    // free deleted node
    free_history_entry(entry);
}

// free a entry and its contents
void free_history_entry(struct history_entry* entry) {
    if (!entry) {
        return;
    }
    if (entry->input_string) {
        free(entry->input_string);
    }
    free(entry);
}

// resets the history index for get_next and get_previous
void reset_history_index() {
    history_current = history_tail;
}

struct history_entry* get_entry_by_string(char* input_string) {
    // input string is null
    if (!input_string) {
        return NULL;
    }
    // start from first entry
    struct history_entry* current_entry = history_head;
    // while not at end -> continue searching
    while (current_entry) {
        // chekc if entry content matches string
        if (strcmp(input_string, current_entry->input_string) == 0) {
            return current_entry;
        }
        // look at next entry
        current_entry = current_entry->next_entry;
    }
    // return null if not found
    return NULL;
}

// gets the histiry entry with the next higher index
char* get_next_history_entry_string() {
    if (!history_current) {
        return NULL;
    }
    char* input_string = history_current->input_string;
    if (history_current->next_entry) {
        history_current = history_current->next_entry;
    }
    return input_string;
}

// gets the history entry with the next lower index
char* get_previous_history_entry_string() {
    if (!history_current) {
        return NULL;
    }
    char* input_string = history_current->input_string;
    if (history_current->previous_entry) {
        history_current = history_current->previous_entry;
    }
    return input_string;
}

// gets the n-th entry from the back, starting with 0
char* get_nth_history_entry_string(int index) {
    // index out of bounds
    if (index >= history_size) {
        return NULL;
    }
    // iterate through list to get n-th element
    struct history_entry* entry = history_head;
    for (int counter = 0; counter < history_size; counter++) {
        entry = entry->next_entry;
    }
    return entry->input_string;
}