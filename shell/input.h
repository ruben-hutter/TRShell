#ifndef INPUT_H
#define INPUT_H

// stands for special return values
// const char EOF_ = -1;
// const char ERRCHAR = 0;
#define EOF_ -1
#define ERRCHAR 0

// init value for the curpos field 
// const long INIT_POS = -2;
#define INIT_POS -2L

struct input_struct {   
    char* buffer;           // the input text
    long buffer_size;       // size of the input text
    long current_pos;       // absolute char position in source
};

// populates the passed dstruct with the passed string
void populate_struct(struct input_struct input_struct, char* input_string);
// get next char from buffer
char get_next_char(struct input_struct* input);
// moves the read index one char back
void unget_last_char(struct input_struct* input);
// returns the next char without moving the read index
char peek_next_char(struct input_struct* input);

void skip_white_spaces(struct input_struct* input);

#endif
