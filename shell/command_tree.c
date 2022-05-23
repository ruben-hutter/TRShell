#include "command_tree.h"

struct tree_node* new_node(enum node_type_e type) {
    struct tree_node* node = malloc(sizeof(struct tree_node));

    if (!node) {
        return NULL;
    }

    memset(node, 0, sizeof(struct tree_node));
    node->type = type;

    return node;
}

void add_child_node(struct tree_node* parent, struct tree_node* child) {
    if (!parent || !child) {
        return;
    }

    if (!parent->first_child) {
        parent->first_child = child;
    } else {
        struct tree_node* sibling = parent->first_child;

        while (sibling->next_sibling) {
            sibling = sibling->next_sibling;
        }

        sibling->next_sibling = child;
        child->prev_sibling = sibling;
    }
    parent->children++;
}

void set_node_val_str(struct tree_node* node, char* val) {
    node->val_type = VAL_STR;

    if (!val) {
        node->val.str = NULL;
    } else {
        char* val2 = malloc(strlen(val) + 1);

        if (!val2) {
            node->val.str = NULL;
        } else {
            strcpy(val2, val);
            node->val.str = val2;
        }
    }
}

void free_node_tree(struct tree_node* node) {
    if (!node) {
        return;
    }

    struct tree_node* child = node->first_child;

    while (child) {
        struct tree_node* next = child->next_sibling;
        free_node_tree(child);
        child = next;
    }

    if (node->val_type == VAL_STR) {
        if (node->val.str) {
            free(node->val.str);
        }
    }
    free(node);
}
