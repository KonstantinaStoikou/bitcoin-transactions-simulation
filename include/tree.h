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
Tree_node *allocate_tree_node(void *data);
// Add receiver of a transaction for a given bitcoin "share" (tree node)
Tree_node *add_receiver(Tree_node *node, void *data);
// Add sender of a transaction for a given bitcoin "share" (tree node)
Tree_node *add_sender(Tree_node *node, void *data);

#endif