#include <stdio.h>

#include "string_utils.h"
#include "autocomplete.h"

int main(int argc, char** argv) {
    char* str1 = "cd os/proj/trsh\\ shell/shell\\ s";
    char* str2 = "cd os/proj/\"trsh shell\"/\"shell s";
    char* str3 = "cd \"os/proj/trsh shell/shell s";
    char* str4 = "cd /path/o";
    char* string = get_malloced_copy(str4);
    struct approach_split* my_split;
    my_split = auto_string_manip(string);
    free(string);
    free(my_split);
    return 0;
}
