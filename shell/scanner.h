#ifndef SCANNER_H
#define SCANNER_H

struct token_struct {
    struct input_struct* input;     /* source of input */
    int text_len;                   /* length of token */
    char* text;                     /* token */
};

/* the special EOF token, which indicates the end of input */
extern struct token_struct eof_token;

struct token_struct* tokenize(struct input_struct* input);
void free_token(struct token_struct* token);

#endif
