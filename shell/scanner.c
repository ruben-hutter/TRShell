#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "shell.h"
#include "scanner.h"
#include "input.h"

char* token_buffer = NULL;
int token_buffer_size = 0;
int token_buffer_index = -1;

/* special token to indicate end of input */
struct token_struct eof_token = {
    .text_len = 0
};


void add_to_buffer(char c) {
    token_buffer[token_buffer_index++] = c;

    if (token_buffer_index >= token_buffer_size) {
        char* tmp = realloc(token_buffer, token_buffer_size * 2);

        if (!tmp) {
            errno = ENOMEM;
            return;
        }
        token_buffer = tmp;
        token_buffer_size *= 2;
    }
}

struct token_struct* create_token(char* str) {
    struct token_struct* token = malloc(sizeof(struct token_struct));

    if(!token) {
        return NULL;
    }

    memset(token, 0, sizeof(struct token_struct));
    token->text_len = strlen(str);

    char* next_str = malloc(token->text_len + 1);

    if (!next_str) {
        free(token);
        return NULL;
    }

    strcpy(next_str, str);
    token->text = next_str;

    return token;
}

void free_token(struct token_struct* token) {
    if (token->text) {
        free(token->text);
    }
    free(token);
}

struct token_struct* tokenize(struct input_struct* input) {
    int end_loop = false;

    if (!input || !input->buffer || !input->buffer_size) {
        errno = ENODATA;
        return &eof_token;
    }

    if (!token_buffer) {
        token_buffer_size = 1024;
        token_buffer = malloc(token_buffer_size);
        if (!token_buffer) {
            errno = ENOMEM;
            return &eof_token;
        }
    }

    token_buffer_index = 0;
    token_buffer[0] = '\0';

    char next_char = get_next_char(input);

    if (next_char == ERRCHAR || next_char == EOF) {
        return &eof_token;
    }

    do {
        switch (next_char) {
            case ' ':
                break;
            case '\t':
                if (token_buffer_index > 0) {
                    end_loop = true;
                }
                break;
            case '\n':
                if (token_buffer_index > 0) {
                    inget_char(input);
                } else {
                    add_to_buffer(next_char);
                }
                end_loop = true;
                break;
            default:
                add_to_buffer(next_char);
                break;
        }

        if (end_loop) {
            break;
        }
    } while ((next_char = get_next_char(input)) != EOF);

    if (token_buffer_index == 0) {
        return &eof_token;
    }

    if (token_buffer_index >= token_buffer_size) {
        token_buffer_index--;
    }
    token_buffer[token_buffer_index] = '\0';

    struct token_struct* token = create_token(token_buffer);
    if (!token) {
        fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
        return &eof_token;
    }

    token->input = input;
    return token;
}
