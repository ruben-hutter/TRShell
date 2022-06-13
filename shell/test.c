#include <stdio.h>

#include "string_utils.h"

struct approach_split {
    char* pre;
    char* path;
    char* n_complete;
};

struct approach_split* auto_string_manip(char* string);
void format_n_complete(char** n_complete);

int main(int argc, char** argv) {
    char* str1 = "cd os/proj/trsh\\ shell/shell\\ s";
    char* str2 = "cd os/proj/\"trsh shell\"/\"shell s";
    char* str3 = "cd \"os/proj/trsh shell/shell s";
    char* str4 = "cd /path/o";
    char* string1 = get_malloced_copy(str1);
    char* string2 = get_malloced_copy(str2);
    char* string3 = get_malloced_copy(str3);
    struct approach_split* my_split;
    my_split = auto_string_manip(string1);
    printf("-------------------\n");
    my_split = auto_string_manip(string2);
    printf("-------------------\n");
    my_split = auto_string_manip(string3);
    free(string1);
    free(string2);
    free(string3);
    free(my_split);
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
    printf("pre: [%s]\n", m_pre);

    // get n_complete
    char* n_complete = strrchr(string, slash);
    if (!n_complete) {
        // path not partially given
        // take rest after command
        unsigned int n_complete_len = string_len - pre_len - 1;
        m_n_complete = get_malloced_empty_string(n_complete_len);
        strncpy(m_n_complete, pre + 1, n_complete_len);
        printf("n_complete: [%s]\n", m_n_complete);
        // format n_complete
        format_n_complete(&m_n_complete);
        // bind everything to struct
        app_split->pre = m_pre;
        app_split->n_complete = m_n_complete;
        return app_split;
    }
    unsigned int n_complete_len = (string + string_len) - n_complete - 1;
    m_n_complete = get_malloced_empty_string(n_complete_len);
    strncpy(m_n_complete, n_complete + 1, n_complete_len);
    // format n_complete
    format_n_complete(&m_n_complete);
    printf("n_complete: [%s]\n", m_n_complete);

    // get path
    unsigned int path_len = string_len - pre_len - n_complete_len;
    m_path = get_malloced_empty_string(path_len);
    strncpy(m_path, pre + 1, path_len);
    printf("path: [%s]\n", m_path);

    // bind everything to struct
    app_split->pre = m_pre;
    app_split->path = m_path;
    app_split->n_complete = m_n_complete;
    return app_split;
}

// format n_complete string
void format_n_complete(char** n_complete) {
    char* single_quotes = "'";
    char* back_n_quotes = "\\\"";
    // remove double-quotes & backslashes
    remove_chars_from_string(*n_complete, back_n_quotes);
    // put between single-quotes
    string_bwn_char(n_complete, single_quotes);
}
