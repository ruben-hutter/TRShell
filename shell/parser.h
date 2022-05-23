#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>

#include "main.h"
#include "command_tree.h"
#include "token_builder.h"    /* token_struct */
#include "buffered_string.h"      /* input_struct */

struct tree_node* build_tree_from_root(struct token* token);

#endif
