#include "ht.h"

void ht(int argc, char** argv) {
    if (argc < 2) {
        // ht without arguments -> dump history
        print_history();
    } else {
        char* history_index = *(argv+1);
        recall_history();
    }
}

void recall_history() {
    printf(">>> imagine accessing a history element!\n");
    return;
}