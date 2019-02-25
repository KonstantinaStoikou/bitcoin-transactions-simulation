#include "../include/tree.h"
#include <stdlib.h>

Tree *initialize_tree(void) {
    Tree *tree = NULL;
    tree = malloc(sizeof(Tree));
    tree->root = NULL;

    return tree;
}

Tree_node *allocate_tree_node(void *data) {
    Tree_node *new_node = (Tree_node *)malloc(sizeof(Tree_node));
    new_node->data = data;
    new_node->receiver = NULL;
    new_node->sender = NULL;
    return new_node;
}

Tree_node *add_receiver(Tree_node *node, void *data) {
    // Allocate memory for node
    Tree_node *new_node = allocate_tree_node(data);
    // Make right child of given node point to it
    node->receiver = new_node;

    return 0;
}

Tree_node *add_sender(Tree_node *node, void *data) {
    // Allocate memory for node
    Tree_node *new_node = allocate_tree_node(data);
    // Make left child of given node point to it
    node->sender = new_node;

    return 0;
}