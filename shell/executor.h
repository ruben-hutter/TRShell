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
#include "node.h"

char* search_path(char* file);
int do_exec_cmd(int argc, char** argv);
int do_simple_command(struct node_struct* node);

#endif
