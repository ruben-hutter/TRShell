#include <unistd.h>

#include "shell.h"
#include "parser.h"
#include "scanner.h"
#include "node.h"
#include "input.h"

struct node_struct* parse_simple_command(struct token_struct* token) {
    if (!token) {
        return NULL;
    }

    struct node_struct* cmd = new_node(NODE_COMMAND);
    if (!cmd) {
        free_token(token);
        return NULL;
    }

    struct input_struct* input = token->input;

    do {
        if (token->text[0] == '\n') {
            free_token(token);
            break;
        }

        struct node_struct* word = new_node(NODE_VAR);
        if (!word) {
            free_node_tree(cmd);
            free_token(token);
            return NULL;
        }
        set_node_val_str(word, token->text);
        add_child_node(cmd, word);

        free_token(token);
    } while ((token = tokenize(input)) != &eof_token);

    return cmd;
}
