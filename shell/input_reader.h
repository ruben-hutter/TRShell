#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "prompt.h"

#define READ_BUFFER_SIZE 1024

// reads user input from the stdin
char* read_from_input();
// checks if character tripple is a control sequence
int is_control_sequence(char* sequence);
// hande control sequence
void handle_control_sequence(char* sequence);

#endif
