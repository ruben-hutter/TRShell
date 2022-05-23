#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>

#include "main.h"
#include "node.h"
#include "scanner.h"    /* token_struct */
#include "buffered_string.h"      /* input_struct */

struct node_struct* parse_simple_command(struct token_struct* token);

#endif
