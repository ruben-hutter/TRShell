#ifndef BUFFERED_STRING_H
#define BUFFERED_STRING_H

#include <errno.h>
#include <string.h>
#include <stdbool.h>

// stands for special return values
// const char EOF_ = -1;
// const char ERRCHAR = 0;
#define EOF_ -1
#define ERRCHAR 0

// init value for the curpos field 
// const long INIT_POS = -2;
#define INIT_POS -1L

struct buffered_string {   
    char* buffer;           // the input text
    long buffer_size;       // size of the input text
    long current_pos;       // absolute char position in source
};

// ceates a buffered string contianing the specified string
void populate_buffered_string_with(struct buffered_string* buffered_string, char* input_string);
// get next char from buffer
char get_next_char(struct buffered_string* input);
// moves the read index one char back
void unget_last_char(struct buffered_string* input);
// returns the next char without moving the read index
char peek_next_char(struct buffered_string* input);

void skip_white_spaces(struct buffered_string* input);

#endif
