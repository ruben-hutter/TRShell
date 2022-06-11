#include "autocomplete.h"

char* autocomplete(char* approach) {
    // just a temporary solution until all all queries are implemented
    return querry_history(approach);
}

// returns the history entry with hte best match
char* querry_history(char* approach) {
    printf("init completion");
    char* current_entry = NULL;
    int appr_length = strlen(approach);
    int best_match_length = 0;
    char* best_entry = NULL;

    // if first letter not match -> ignore
    reset_history_index();
    printf("reste idx");
    while (current_entry = get_next_history_entry_string()) {
        printf("loop outer");
        // if not matching lengths -> ignore
        if (strlen(approach) > strlen(current_entry)) {
            continue;
        }

        // start comparing
        int curr_match_length = 0;
        while ((curr_match_length <= appr_length) && (approach[curr_match_length] == current_entry[curr_match_length])) {
            printf("loop inner");
            curr_match_length++;
        }
        
        // if new best update best
        if (curr_match_length > best_match_length) {
            best_match_length = curr_match_length;
            if (best_entry) {
                free(best_entry);
            }
            best_entry = get_malloced_copy(current_entry);
            printf("new best");
        }
    }
    return best_entry;
}