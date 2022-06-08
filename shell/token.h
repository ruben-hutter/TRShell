#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "shell.h"
#include "buffered_string.h"
#include "string_utils.h"

struct token {
    struct buffered_string* input;     // source of input
    int string_length;                   // length of token
    char* token_string;                     // token
};

// special token to indicate end of input
extern struct token eof_token;
// add a character to the token buffer
void add_to_buffer(char c);
// create new token struct from string
struct token* build_token(char* str);
// frees all allocated spece of a token
void free_token(struct token* token);
// tokenize an input string
struct token* get_next_token(struct buffered_string* input);

#endif
