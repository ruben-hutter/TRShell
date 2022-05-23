#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "main.h"
#include "command_tree.h"

char* search_path(char* file);
int do_exec_cmd(int argc, char** argv);
int do_simple_command(struct tree_node* node);

#endif
