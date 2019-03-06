/**
 * A generic binary tree to store transactions involving a certain bitcoin.
 * It is not a binary search tree, but a tree that each node has two pointers to
 * children, because each bitcoin "share" can participate in a transaction
 * between two people (sender, receiver), so two new "shares" will be created.
 *
 */

#ifndef TREE_HEADER
#define TREE_HEADER

// A node of the tree
typedef struct Tree_node {
    void *data;
    struct Tree_node *receiver;
    struct Tree_node *sender;
} Tree_node;

// A pointer to the root of the tree
typedef struct Tree {
    Tree_node *root;
} Tree;

// Allocate memory for a new tree struct and return it
Tree *initialize_tree(void);
// Allocate memory for a new tree node
Tree_node *allocate_tree_node(void *data, int sizeof_data_struct);
// Add receiver of a transaction for a given bitcoin "share" (tree node)
Tree_node *add_receiver(Tree_node *node, void *data, int sizeof_data_struct);
// Add sender of a transaction for a given bitcoin "share" (tree node)
Tree_node *add_sender(Tree_node *node, void *data, int sizeof_data_struct);
// Print (depth-first) all sender nodes of the tree (first argument root of the
// tree), giving a printing function as argument depending on the data struct
void print_tree_senders(Tree_node *node, void (*fptr)(void *));
// Print all nodes of tree (first argument root of the tree), giving a printing
// function as argument
void print_tree(Tree_node *node, void (*function)(void *));
// Release memory of tree (first argument root of the tree) giving a delete
// function as argument depending on the data struct
void delete_tree(Tree_node **node, void (*function)(void **));

#endif