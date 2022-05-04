#ifndef INPUT_H
#define IMPUT_H

// stants for special return values
const char EOF = -1;
const char ERRCHAR = 0;

// init value for the curpos field 
const long INIT_INPUT_POS = -2;

struct input_struct
{   
    char *buffer;       /* the input text */
    long bufsize;       /* size of the input text */
    long  curpos;       /* absolute char position in source */
};

char next_char(struct source_s *src);
void remove_last_char(struct source_s *src);
char peek_char(struct source_s *src);
void skip_white_spaces(struct source_s *src);

#endif