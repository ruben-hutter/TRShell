#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "node.h"

char* search_path(char* file);
int do_exec_cmd(int argc, char** argv);
int do_simple_command(struct node_struct* node);

#endif
