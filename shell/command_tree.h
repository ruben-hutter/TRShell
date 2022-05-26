#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "token.h"
#include "shell.h"

enum node_type {
    COMMAND_NODE,       /* simple command */
    VARIABLE_NODE            /* variable name (or simply a word) */
};

enum value_type {
    VALUE_SIGNED_INT = 1,       /* signed int */
    VALUE_UNSIGNED_INT,           /* signed int */
    VALUE_SIGNED_LONG_LONG,         /* signed int */
    VALUE_UNSIGNED_LONG_LONG,         /* signed int */
    VALUE_FLOAT,          /* signed int */
    VALUE_LONG_DOUBLE,        /* signed int */
    VALUE_CHAR,            /* signed int */
    VALUE_STRING             /* signed int */
};

union value {
    long signed_int;
    unsigned long unsigned_int;
    long long signed_long_long;
    unsigned long long unsigned_long_long;
    double signed_float;
    long double long_double;
    char character;
    char* string;
};

struct tree_node {
    enum node_type type;              /* type of this node */
    enum value_type value_type;           /* type of this node's val field */
    union value value;                 /* value of this node */
    int number_of_children;                       /* number of child nodes */
    struct tree_node* first_child;    /* first child node */
    /* if this is a child node, keep pointers to prev/next siblings */
    struct tree_node* next_sibling;
    struct tree_node* prev_sibling;
};

struct tree_node* new_node(enum node_type type);
void add_child_node(struct tree_node* parent, struct tree_node* child);
void free_tree_from_root(struct tree_node* node);
void set_node_val_str(struct tree_node* node, char* val);
struct tree_node* build_tree_from_root(struct token* root_token);

#endif
