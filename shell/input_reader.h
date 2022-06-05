#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>  

#include "prompt.h"

#define READ_BUFFER_SIZE 1024

// reads user input from the stdin
char* read_from_input();

int get_string_from_input(char* buffer, int buffer_size);

// hande control sequence
void handle_control_sequence(char* sequence);

/*set tty mode to raw*/
void set_tty_raw();

/*restore the old settings*/
void restore_old_tty_settings();

#endif
