#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

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

struct tree_node {
    enum node_type_e type;              /* type of this node */
    enum val_type_e val_type;           /* type of this node's val field */
    union symval_u val;                 /* value of this node */
    int children;                       /* number of child nodes */
    struct tree_node* first_child;    /* first child node */
    /* if this is a child node, keep pointers to prev/next siblings */
    struct tree_node* next_sibling;
    struct tree_node* prev_sibling;
};

struct tree_node* new_node(enum node_type_e type);
void add_child_node(struct tree_node* parent, struct tree_node* child);
void free_tree_from_root(struct tree_node* node);
void set_node_val_str(struct tree_node* node, char* val);

#endif
