#include<stdio.h>

#include"string_utils.h"


int main(void){   
    char* test_string = get_malloced_copy("0123456789");
    shift_string_left(test_string, 5, 9);
    printf(test_string);
    free(test_string);
    return 0;
}