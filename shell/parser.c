#include "parser.h"

struct tree_node* build_tree_from_root(struct token* token) {
    // nullpointer -> exit
    if (!token) {
        return NULL;
    }
    // allocate new node for command
    struct tree_node* root_node = new_node(NODE_COMMAND);
    // allocation failed -> return and free token as not used anymore
    if (!root_node) {
        free_token(token);
        return NULL;
    }
    // get original buffered input from token
    struct buffered_string* input = token->input;

    do {
        // if token starts with newline -> abort
        if (token->token_string[0] == '\n') {
            free_token(token);
            break;
        }
        // allocate new tree node for a word of the input
        struct tree_node* word = new_node(NODE_VAR);
        // aloc failed
        if (!word) {
            // free cmd node prepared earlier
            free_node_tree(root_node);
            // free passed token as no longer used
            free_token(token);
            return NULL;
        }
        // make new node to string node contianing the current word
        set_node_val_str(word, token->token_string);
        // set new node as a child of the cmd "head_node"
        add_child_node(root_node, word);
        // free token
        free_token(token);
    } while ((token = get_next_token(input)) != &eof_token);

    return root_node;
}
