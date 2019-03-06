#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tree *initialize_tree(void) {
    Tree *tree = NULL;
    tree = malloc(sizeof(Tree));
    tree->root = NULL;

    return tree;
}

Tree_node *allocate_tree_node(void *data, int sizeof_data_struct) {
    Tree_node *new_node = (Tree_node *)malloc(sizeof(Tree_node));
    new_node->data = malloc(sizeof_data_struct);
    memcpy(new_node->data, data, sizeof_data_struct);
    new_node->receiver = NULL;
    new_node->sender = NULL;
    return new_node;
}

Tree_node *add_receiver(Tree_node *node, void *data, int sizeof_data_struct) {
    // Allocate memory for node
    Tree_node *new_node = allocate_tree_node(data, sizeof_data_struct);
    // Make right child of given node point to it
    node->receiver = new_node;

    return 0;
}

Tree_node *add_sender(Tree_node *node, void *data, int sizeof_data_struct) {
    // Allocate memory for node
    Tree_node *new_node = allocate_tree_node(data, sizeof_data_struct);
    // Make left child of given node point to it
    node->sender = new_node;

    return 0;
}

// Give a printing function as argument depending on the data struct
void print_tree_senders(Tree_node *node, void (*function)(void *)) {
    if (node == NULL) {
        return;
    }
    (*function)(node->data);
    printf("\n");

    if (node->sender != NULL) {
        (*function)(node->sender->data);
        printf("\n");
    }
    print_tree_senders(node->sender, function);
    print_tree_senders(node->receiver, function);
}

void print_tree(Tree_node *node, void (*function)(void *)) {
    if (node == NULL) {
        return;
    }
    (*function)(node->data);
    printf("\n");
    print_tree_senders(node->sender, function);
    print_tree_senders(node->receiver, function);
}

void delete_tree(Tree_node **node, void (*function)(void **)) {
    if (*node == NULL) {
        return;
    }

    delete_tree(&(*node)->sender, function);
    delete_tree(&(*node)->receiver, function);
    // if a delete function was given, delete data with it
    if (*function != NULL) {
        (*function)(&(*node)->data);
    }
    // free(node);
}