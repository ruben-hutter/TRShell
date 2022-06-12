#include<stdio.h>

#include"string_utils.h"

int main(void) {
    char* string = "asds  ";
    printf("is single word: %d\n", is_single_word(string));
    return 0;
}
