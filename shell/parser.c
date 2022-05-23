#include <unistd.h>

#include "shell.h"
#include "parser.h"
#include "scanner.h"
#include "node.h"
#include "input.h"

struct node_struct* parse_simple_command(struct token_struct* token) {
    // nullpointer -> exit
    if (!token) {
        return NULL;
    }
    // allocate new node for command
    struct node_struct* cmd = new_node(NODE_COMMAND);
    // allocation failed -> return and free token as not used anymore
    if (!cmd) {
        free_token(token);
        return NULL;
    }
    // get original buffered input from token
    struct input_struct* input = token->input;

    do {
        // if token starts with newline -> abort
        if (token->text[0] == '\n') {
            free_token(token);
            break;
        }
        // allocate new tree node for a word of the input
        struct node_struct* word = new_node(NODE_VAR);
        // aloc failed
        if (!word) {
            // free cmd node prepared earlier
            free_node_tree(cmd);
            // free passed token as no longer used
            free_token(token);
            return NULL;
        }
        // make new node to string node contianing the current word
        set_node_val_str(word, token->text);
        // set new node as a child of the cmd "head_node"
        add_child_node(cmd, word);
        // free token
        free_token(token);
    } while ((token = tokenize(input)) != &eof_token);

    return cmd;
}
