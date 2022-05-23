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

void free_tree_from_root(struct tree_node* node) {
    if (!node) {
        return;
    }

    struct tree_node* child = node->first_child;

    while (child) {
        struct tree_node* next = child->next_sibling;
        free_tree_from_root(child);
        child = next;
    }

    if (node->val_type == VAL_STR) {
        if (node->val.str) {
            free(node->val.str);
        }
    }
    free(node);
}

struct tree_node* build_tree_from_root(struct token* root_token) {
    // nullpointer -> exit
    if (!root_token) {
        return NULL;
    }
    // allocate new node for command
    struct tree_node* root_node = new_node(NODE_COMMAND);
    // allocation failed -> return and free token as not used anymore
    if (!root_node) {
        free_token(root_token);
        return NULL;
    }
    // get original buffered input from token
    struct buffered_string* input = root_token->input;

    do {
        // if token starts with newline -> abort
        if (root_token->token_string[0] == '\n') {
            free_token(root_token);
            break;
        }
        // allocate new tree node for a word of the input
        struct tree_node* word = new_node(NODE_VAR);
        // aloc failed
        if (!word) {
            // free cmd node prepared earlier
            free_tree_from_root(root_node);
            // free passed token as no longer used
            free_token(root_token);
            return NULL;
        }
        // make new node to string node contianing the current word
        set_node_val_str(word, root_token->token_string);
        // set new node as a child of the cmd "head_node"
        add_child_node(root_node, word);
        // free token
        free_token(root_token);
    } while ((root_token = get_next_token(input)) != &eof_token);

    return root_node;
}
