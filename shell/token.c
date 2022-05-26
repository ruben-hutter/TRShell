#include "token.h"

char* token_buffer = NULL;
int token_buffer_size = 0;
int token_buffer_index = -1;

struct token eof_token = {
    .string_length = 0
};

// add a character to the token buffer
void add_to_buffer(char c) {
    // append char to end of buffer
    token_buffer[token_buffer_index++] = c;

    // buffer full -> extend size
    if (token_buffer_index >= token_buffer_size) {
        // realloc buffer with double the previous size
        char* tmp = realloc(token_buffer, token_buffer_size * 2);
        // could not allocate buffer -> return
        if (!tmp) {
            errno = ENOMEM;
            return;
        }
        // update buffer pointer of new buffer and updaste size
        token_buffer = tmp;
        token_buffer_size *= 2;
    }
}

// create new token struct from string
struct token* build_token(char* str) {
    // allocate new token struct
    struct token* token = malloc(sizeof(struct token));
    //could not allocate struct -> return
    if(!token) {
        return NULL;
    }

    memset(token, 0, sizeof(struct token));
    // set token_string length of token to string length of the input string
    token->string_length = strlen(str);
    // alloc space for temp string
    char* next_str = malloc(token->string_length + 1);
    // could not allocate space for temp string -> return
    if (!next_str) {
        free(token);
        return NULL;
    }
    // copy input string to temp string
    strcpy(next_str, str);
    // set tokens string to temp string
    token->token_string = next_str;

    return token;
}

// frees all allocated spece of a token
void free_token(struct token* token) {
    if (token->token_string) {
        // if token allocated space for string -> free
        free(token->token_string);
    }
    // free space of token itself
    free(token);
}

// tokenize an input string
struct token* get_next_token(struct buffered_string* input) {
    int end_loop = false;

    // pointers to input struct or it's members are null -> return
    if (!input || !input->buffer || !input->buffer_size) {
        errno = ENODATA;
        return &eof_token;
    }

    // token buffer does noes not exist -> create it
    if (!token_buffer) {
        token_buffer_size = 1024;
        token_buffer = malloc(token_buffer_size);
        // could not allocate buffer -> return
        if (!token_buffer) {
            errno = ENOMEM;
            return &eof_token;
        }
    }

    token_buffer_index = 0;
    make_empty_string(token_buffer);

    // get next char from input buffer
    char next_char = get_next_char(input);

    // ??? if end of file ore useless content -> return
    if (next_char == ERRCHAR || next_char == EOF) {
        return &eof_token;
    }

    // do while not reached end of string...
    do {
        switch (next_char) {
            // ignore whitespaces
            case ' ':
                // no there isn't a break missing here!!!
            case '\t':
                // stop processing if tab found in string (NOT AT BEGINNING)
                if (token_buffer_index > 0) {
                    end_loop = true;
                }
                // ignore tab at beginning of input string
                break;
            // handle newline and stop processing
            case '\n':
                if (token_buffer_index > 0) {
                    // ignore newline and unget char if inside of string
                    unget_last_char(input);
                } else {
                    // add newline to buffer if at beginning of string
                    add_to_buffer(next_char);
                }
                // stop processing
                end_loop = true;
                break;
            // if not special character -> append to buffer
            default:
                add_to_buffer(next_char);
                break;
        }
    } while (!end_loop && (next_char = get_next_char(input)) != EOF);

    // if nothing appended to buffer -> return
    if (token_buffer_index == 0) {
        return &eof_token;
    }

    // if buffer is full (can't happen as handled in add_to_buffer(char* str))
    // -> move pointer back into buffer and add terminator... WHY???
    if (token_buffer_index >= token_buffer_size) {
        token_buffer_index--;
    }
    token_buffer[token_buffer_index] = '\0';

    // create new token containing the buffered string as it's content string
    struct token* token = build_token(token_buffer);
    // could not allocate space for token -> print error
    if (!token) {
        fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
        return &eof_token;
    }
    // add pointer to input buffer to token
    // contains the original input string that was used to construct the tokens content string
    token->input = input;
    
    return token;
}
