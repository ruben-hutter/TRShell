#include "autocomplete.h"

char* autocomplete(char* approach) {
    // just a temporary solution until all all queries are implemented
    return querry_history(approach);
}

// returns the history entry with hte best match
char* querry_history(char* approach) {
    char* current_entry = NULL;
    int appr_length = strlen(approach);
    int best_match_length = 0;
    char* best_entry = NULL;

    // if first letter not match -> ignore
    reset_history_index();
    while (!is_at_head()) {
        current_entry = get_previous_history_entry_string();
        // if not matching lengths -> ignore
        if (strlen(approach) > strlen(current_entry)) {
            continue;
        }

        // start comparing
        int curr_match_length = 0;
        while ((curr_match_length <= appr_length) && (approach[curr_match_length] == current_entry[curr_match_length])) {
            curr_match_length++;
        }
        
        // if new best update best
        if (curr_match_length > best_match_length) {
            best_match_length = curr_match_length;
            if (best_entry) {
                free(best_entry);
            }
            best_entry = get_malloced_copy(current_entry);
            cut_at_trailing_newline(best_entry);
        }
    }
    return best_entry;
}