#ifndef WORD_EXPANSION_H
#define WORD_EXPANSION_H

#include <string.h>

struct word {
    char* string;
    int string_length;
    struct word* next_word;
};

struct word* get_word_from(char* string);
void free_words_from(struct word* first_word);
char* get_string_from_words(struct word *first_word);
int is_name(char* string);
size_t get_closing_quote_index(char* string);
size_t get_closing_brace_index(char* string);
int substitute_word(char** start_pointer, char** pointer, size_t length, char*(func)(char*), int add_quotes);

/*
 * allready in c file
 */
char* expand_tilde(char* string);
size_t find_closing_quote(char* data);
size_t find_closing_brace(char* data);

#endif
