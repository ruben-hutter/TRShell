#include "ht.h"

void ht(int argc, char** argv) {
    if (argc < 2) {
        // ht without arguments -> dump history
        print_history();
    } else {
        char* history_index = *(argv+1);
        recall_history(atoi(*(argv+1)));
    }
}

void recall_history(int index) {
    // cereate new buffered string to execute
    struct buffered_string buffered_input;
    // recall command from history
    char* hist_string = get_nth_history_entry_string(index);
    // if recalled failed -> index was out of bounds
    if (!hist_string) {
        printf("Index %d out of the history list of length %d!\n", index, history_size);
        return;
    }
    printf("RETRIEVED> %s", hist_string);
    //hist_string = get_malloced_copy(hist_string);
    // update history as command will be called
    // append_string_to_history(hist_string);
    // populate the buffered string
    //populate_buffered_string(&buffered_input, hist_string);
    //parse_and_execute(&buffered_input);
    
    return;
}