#include "command_tree.h"

// create new node to be added to the tree
struct tree_node* new_node(enum node_type type) {
    // allocate space for the node
    struct tree_node* node = malloc(sizeof(struct tree_node));
    // could not allocate space -> exit
    if (!node) {
        return NULL;
    }
    // erase data in allocated space (overwrite with 0)
    memset(node, 0, sizeof(struct tree_node));
    // set node to specified type
    node->type = type;
    return node;
}

// add node as child to parent node
// TODO: more cnsise implementation using pure doubl linked list (no first child)
void add_child_node(struct tree_node* parent, struct tree_node* child) {
    // if any null pointers -> exit
    if (!parent || !child) {
        return;
    }

    // add child
    // if no child yet, add child as first child
    if (!parent->first_child) {
        
        parent->first_child = child;
        parent->number_of_children++;
        return;
    }

    // iterate down the list of children until last reached
    struct tree_node* sibling = parent->first_child;
    while (sibling->next_sibling) {
        sibling = sibling->next_sibling;
    }
    // append to list and set pointers in both direcitons (doubly linked list)
    sibling->next_sibling = child;
    child->prev_sibling = sibling;
    parent->number_of_children++;
}

void set_node_val_str(struct tree_node* node, char* string) {
    // set node type to string node
    node->value_type = VALUE_STRING;

    // if passd string pinter is null
    if (!string) {
        node->value.string = NULL;
        return;
    }
    
    // alloc space for passed string
    char* node_string = malloc(strlen(string) + 1);

    // alloc failed
    if (!node_string) {
        node->value.string = NULL;
        return;
    }
    
    // copy and set node's string
    strcpy(node_string, string);
    node->value.string = node_string;
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

    if (node->value_type == VALUE_STRING && node->value.string) {
        free(node->value.string);
    }

    free(node);
}

struct tree_node* build_tree_from_root(struct token* root_token) {
    // nullpointer -> exit
    if (!root_token) {
        return NULL;
    }
    // allocate new node for command
    struct tree_node* root_node = new_node(COMMAND_NODE);
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

        // allocate new tree node for a token of the input
        struct tree_node* node = new_node(VARIABLE_NODE);
        // alloc failed
        if (!node) {
            // free cmd node prepared earlier
            free_tree_from_root(root_node);
            // free passed token as no longer used
            free_token(root_token);
            return NULL;
        }
        // make new node to string node contianing the current token
        set_node_val_str(node, root_token->token_string);
        // set new node as a child of the cmd "head_node"
        add_child_node(root_node, node);
        // free token
        free_token(root_token);
    } while ((root_token = get_next_token(input)) != &eof_token);

    return root_node;
}

void print_command_tree(struct tree_node* node) {
    // traverse tree and print out nodes
    if (!node) {
        return;
    }

    int i = 0;

    struct tree_node* child = node->first_child;

    while (child) {
        struct tree_node* next = child->next_sibling;
        printf("child %d: %s -> ", i++, child->value.string);
        child = next;
    }
    printf("\n");
}
