#include <errno.h>

#include <stdbool.h>

#include "shell.h"
#include "input.h"

// moves the current read position back by one
void unget_last_char (struct input_struct *input) {
    // no char to remove as positioned at beginning of buffer
    if (input->current_pos < 0) {
        return;
    }
    // remove last char by moving pointer in front of that char
    input->current_pos--;
}

// returns the next char in the buffer
char get_next_char (struct input_struct *input) {
    // either input_struct pointer or pointer of buffer in input struct is NULL       
    if (!input || !input->buffer) {
        // return error char symbolizing that an error occured
        errno = ENODATA;
        return ERRCHAR;
    }

    if (input->current_pos == INIT_POS) {
        // init buffer position
        input->current_pos  = -1;
    }

    input++;
    // if next symbol is outside of buffer cause reached end
    if (input->current_pos >= input->buffer_size) {
        // set position to last char in buffer
        input->current_pos = input->buffer_size;
        // return end of file char
        return EOF;
    }

    // return char at current buffer position
    return input->buffer[input->current_pos];
}

// return the next char without incrementinng the current read potision
char peek_next_char(struct input_struct *input) {
    // either input_struct pointer or pointer of buffer in input struct is NULL
    if (!input || !input->buffer) {
        // return error char symbolizing that an error occured
        errno = ENODATA;
        return ERRCHAR;
    }

    // current reading position in the buffer used for getting the pos of the next char
    long peek_pos = input->current_pos;

    // if peek is at buffer init position -> set one before first char
    if (peek_pos == INIT_POS) {
        peek_pos = -1;
    }

    // increment peek pos to peek at next char
    peek_pos++;

    // if peeking out of buffer return end of file
    if (peek_pos >= input->buffer_size) {
        return EOF;
    }

    return input->buffer[peek_pos];
}

// moves the reading position in the buffer to the right until non whitespace char is found
void skip_white_spaces(struct input_struct *input) {
    // either input_struct pointer or pointer of buffer in input struct is NULL
    if (!input || !input->buffer) {
        return;
    }

    char upcoming_char;
    // move to the right until non tab or whitespace or EOF char is found
    while (true) {
        upcoming_char = peek_char(input);

        // reached end of file
        if (upcoming_char == EOF) {
            break;
        }

        // read non tab or whitespace char
        if (!(upcoming_char == ' ' || upcoming_char == '\t')) {
            break;
        }
        next_char(input);
    }
}