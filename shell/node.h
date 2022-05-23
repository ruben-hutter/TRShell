#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "main.h"
#include "parser.h"

enum node_type_e {
    NODE_COMMAND,       /* simple command */
    NODE_VAR            /* variable name (or simply a word) */
};

enum val_type_e {
    VAL_SINT = 1,       /* signed int */
    VAL_UINT,           /* signed int */
    VAL_SLLONG,         /* signed int */
    VAL_ULLONG,         /* signed int */
    VAL_FLOAT,          /* signed int */
    VAL_LDOUBLE,        /* signed int */
    VAL_CHR,            /* signed int */
    VAL_STR             /* signed int */
};

union symval_u {
    long sint;
    unsigned long uint;
    long long sllong;
    unsigned long long ullong;
    double sfloat;
    long double ldouble;
    char chr;
    char* str;
};

struct node_struct {
    enum node_type_e type;              /* type of this node */
    enum val_type_e val_type;           /* type of this node's val field */
    union symval_u val;                 /* value of this node */
    int children;                       /* number of child nodes */
    struct node_struct* first_child;    /* first child node */
    /* if this is a child node, keep pointers to prev/next siblings */
    struct node_struct* next_sibling;
    struct node_struct* prev_sibling;
};

struct node_struct* new_node(enum node_type_e type);
void add_child_node(struct node_struct* parent, struct node_struct* child);
void free_node_tree(struct node_struct* node);
void set_node_val_str(struct node_struct* node, char* val);

#endif
