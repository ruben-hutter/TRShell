#include "buffered_string.h"

// populates the passed dstruct with the passed string
void populate_buffered_string_with(struct buffered_string* buffered_string, char* input_string) {
    buffered_string->buffer = input_string;
    buffered_string->buffer_size = strlen(input_string);
    buffered_string->current_pos = INIT_POS;
}

// moves the current read position back by one
void unget_last_char (struct buffered_string* input) {
    // no char to remove as positioned at beginning of buffer
    if (input->current_pos < 0) {
        return;
    }
    // remove last char by moving pointer in front of that char
    input->current_pos--;
}

// returns the next char in the buffer
char get_next_char (struct buffered_string* input) {
    // either buffered_string pointer or pointer of buffer in input struct is NULL       
    if (!input || !input->buffer) {
        // return error char symbolizing that an error occured
        errno = ENODATA;
        return ERRCHAR;
    }
    // increase read position to read next char
    input->current_pos++;
    // if next symbol is outside of buffer cause reached end
    if (input->current_pos >= input->buffer_size) {
        // set position to last char in buffer
        input->current_pos = input->buffer_size;
        // return end of file char
        return EOF_;
    }
    // return char at current buffer position
    return input->buffer[input->current_pos];
}

// return the next char without incrementinng the current read potision
char peek_next_char(struct buffered_string* input) {
    // either buffered_string pointer or pointer of buffer in input struct is NULL
    if (!input || !input->buffer) {
        // return error char symbolizing that an error occured
        errno = ENODATA;
        return ERRCHAR;
    }
    // current reading position in the buffer used for getting the pos of the next char
    long peek_pos = input->current_pos + 1;
    // if peeking out of buffer return end of file
    if (peek_pos >= input->buffer_size) {
        return EOF_;
    }
    return input->buffer[peek_pos];
}

// moves the reading position in the buffer to the right until non whitespace char is found
void skip_white_spaces(struct buffered_string* input) {
    // either buffered_string pointer or pointer of buffer in input struct is NULL
    if (!input || !input->buffer) {
        return;
    }

    char upcoming_char;
    // move to the right until non tab or whitespace or EOF char is found
    while (true) {
        // peek next char
        upcoming_char = peek_next_char(input);
        // reached end of file
        if (upcoming_char == EOF_) {
            break;
        }
        // read non tab or whitespace char
        if (!(upcoming_char == ' ' || upcoming_char == '\t')) {
            break;
        }
        // consume character
        get_next_char(input);
    }
}
