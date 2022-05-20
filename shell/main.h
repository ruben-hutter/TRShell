#ifndef MAIN_H
#define MAIN_H

#include "input.h"

int main(int argc, char **argv);
char* read_from_input();
int parse_and_execute(struct input_struct* input);

#endif
