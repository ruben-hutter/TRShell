#include<stdio.h>

#include"string_utils.h"

int main(void) {
    // char* str1 = "cd os/proj/trsh\\ shell/shell\\ s";
    // char* str2 = "cd os/proj/\"trsh shell\"/\"shell s";
    // char* str3 = "cd \"os/proj/trsh shell/shell s";
    // char* str4 = "cd o";
    // char* string = get_malloced_copy(str4);
    // auto_string_manip(string);
    // free(string);
    char* test = "shell s";
    char* m_test = get_malloced_copy(test);
    string_bwn_char(&m_test, "'");
    free(m_test);
    return 0;
}
