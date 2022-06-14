#include <stdio.h>

#include "string_utils.h"

struct approach_split {
    char* pre;
    char* path;
    char* esc_path;
    char* n_complete;
};

struct approach_split* auto_string_manip(char* string);
void remove_back_n_quotes(char** string);

int main(int argc, char** argv) {
    char* string = "cd q";
    char* str = get_malloced_copy(string);
    struct approach_split* app_split = auto_string_manip(string);
    printf("struct: %s\n", app_split->pre);
    printf("struct: %s\n", app_split->path);
    printf("struct: %s\n", app_split->esc_path);
    printf("struct: %s\n", app_split->n_complete);
    free(str);
    return 0;
}

// manipulates the given string for autocompletion
struct approach_split* auto_string_manip(char* string) {
    // struct ptr to return
    struct approach_split* app_split = (struct approach_split*)
        malloc(sizeof(struct approach_split));
    // members to bind to struct
    char* m_pre;
    char* m_path;
    char* m_esc_path;
    char* m_n_complete;
    // delimiters
    char slash = '/';
    char space = ' ';
    // input length
    int string_len = strlen(string);

    // get pre
    char* pre = strchr(string, space);
    unsigned int pre_len = pre - string + 1;
    m_pre = get_malloced_empty_string(pre_len);
    strncpy(m_pre, string, pre_len);

    // get n_complete
    char* n_complete = strrchr(string, slash);
    if (!n_complete) {
        // path not partially given
        // take rest after command
        unsigned int n_complete_len = string_len - pre_len;
        m_n_complete = get_malloced_empty_string(n_complete_len);
        strncpy(m_n_complete, pre + 1, n_complete_len);
        // format n_complete
        remove_back_n_quotes(&m_n_complete);
        // bind everything to struct
        app_split->pre = m_pre;
        app_split->n_complete = m_n_complete;
        return app_split;
    }
    unsigned int n_complete_len = (string + string_len) - n_complete - 1;
    m_n_complete = get_malloced_empty_string(n_complete_len);
    strncpy(m_n_complete, n_complete + 1, n_complete_len);
    // format n_complete
    remove_back_n_quotes(&m_n_complete);

    // get esc_path
    unsigned int esc_path_len = string_len - pre_len - n_complete_len;
    m_esc_path = get_malloced_empty_string(esc_path_len);
    strncpy(m_esc_path, pre + 1, esc_path_len);

    // get path
    int quotes_count = count_char_in_word(m_esc_path, '"');
    int backslash_count = count_char_in_word(m_esc_path, '\\');
    unsigned int path_len = esc_path_len - quotes_count - backslash_count;
    m_path = get_malloced_copy(m_esc_path);
    remove_back_n_quotes(&m_path);

    // bind everything to struct
    app_split->pre = m_pre;
    app_split->path = m_path;
    app_split->esc_path = m_esc_path;
    app_split->n_complete = m_n_complete;

    return app_split;
}

// remove backslashes and quotes
void remove_back_n_quotes(char** string) {
    char* back_n_quotes = "\\\"";
    // remove double-quotes & backslashes
    remove_chars_from_string(*string, back_n_quotes);
}
