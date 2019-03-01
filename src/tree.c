#include "../include/tree.h"
#include <stdio.h>
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

// Give a printing function as argument depending on the data struct
void print_tree(Tree_node *node, void (*function)(void *)) {
    if (node == NULL) {
        return;
    }
    (*function)(node->data);
    printf("\n");

    if (node->sender != NULL) {
        (*function)(node->sender->data);
        printf("\n");
    }
    print_tree(node->sender, function);
    print_tree(node->receiver, function);
}