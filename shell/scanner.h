#ifndef SCANNER_H
#define SCANNER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "main.h"
#include "buffered_string.h"
#include "string_utils.h"

struct token_struct {
    struct buffered_string* input;     // source of input
    int text_len;                   // length of token
    char* text;                     // token
};

// special token to indicate end of input
extern struct token_struct eof_token;

// add a character to the token buffer
void add_to_buffer(char c);

// create new token struct from string
struct token_struct* create_token(char* str);

// frees all allocated spece of a token
void free_token(struct token_struct* token);

// tokenize an input string
struct token_struct* tokenize(struct buffered_string* input);


#endif
