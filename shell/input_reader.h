#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>  

#include "prompt.h"

#define READ_BUFFER_SIZE 1024
#define TERMINAL_BACKSPACE 0x7F

// reads user input from the stdin
char* read_from_input();
void handle_tabs(int* buffer_position);
int get_string_from_input(char* buffer, int buffer_size);
void handle_backspace(char* buffer, int* buffer_position, int* buffer_end_position);
// hande control sequence
void handle_control_sequence(char* sequence);
void handle_arrow(char* buffer, int* buff_pos_ptr, int* buff_end_pos_ptr);
void remove_line();
void set_buffer_to_string(char* string, char* buffer, int* buff_pos_ptr, int* buff_end_pos_ptr);
/*set tty mode to raw*/
void set_tty_raw();

/*restore the old settings*/
void restore_old_tty_settings();

#endif
