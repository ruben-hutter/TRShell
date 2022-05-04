#include <errno.h>
#include "shell.h"
#include "input.h"

void remove_last_char(struct input_struct *input)
{
    // no char to remove as positioned at beginning of buffer
    if(input->curpos < 0)
    {
        return;
    }
    // remove last char by moving pointer in front of that char
    input->curpos--;
}

char next_char(struct input_struct *input)
{
    // either input_struct pointer or pointer of buffer in input struct is NULL       
    if(!input || !input->buffer)
    {
        errno = ENODATA;
        return ERRCHAR;
    }

    char c1 = 0;
    if(src->curpos == INIT_SRC_POS)
    {
        src->curpos  = -1;
    }
    else
    {
        c1 = src->buffer[src->curpos];
    }

    if(++src->curpos >= src->bufsize)
    {
        src->curpos = src->bufsize;
        return EOF;
    }

    return src->buffer[src->curpos];
}
