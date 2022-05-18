#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"    /* token_struct */
#include "input.h"      /* input_struct */

struct node_struct* parse_simple_command(struct token_struct* token);

#endif
