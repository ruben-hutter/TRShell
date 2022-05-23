#ifndef SCANNER_H
#define SCANNER_H

struct token_struct {
    struct input_struct* input;     // source of input
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
struct token_struct* tokenize(struct input_struct* input);


#endif
