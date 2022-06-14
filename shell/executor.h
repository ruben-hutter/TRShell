#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "command_tree.h"
#include "shell.h"
#include "builtin_utilities.h"

// tree_node struct defined in command_tree.h
struct tree_node;

// searches a command in all directories listed in PATH
char* search_path(char* file);

// executes a command using execv
int exec_command(int argc, char** argv);

// execute a simple command
int do_simple_command(struct tree_node* node);

#endif
