#include <stdio.h>
#include <string.h>

#include "string_utils.h"
#include "prompt.h"

int main() {
    // test string crop
    char current_working_dir[100] = "/home/ruben";
    getcwd(current_working_dir, sizeof(current_working_dir));
    char delimiter = '/';
    printf("string before crop: %s\n", current_working_dir);
    crop_string_to_end(current_working_dir, delimiter);
    printf("string after crop: %s\n", current_working_dir);

    // test home with tilde substitution
    check_if_home(current_working_dir);
    printf("string after check home: %s\n", current_working_dir);
}