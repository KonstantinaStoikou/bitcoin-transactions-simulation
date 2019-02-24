#include "../include/list.h"
#include <stdlib.h>

List *initialize_list(void) {
    List *list = NULL;
    list = malloc(sizeof(List));
    list->head = NULL;

    return list;
}

Node *add_node(List **list, void *data) {
    // Allocate memory for node
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = (*list)->head;
    // Change head pointer as new node is added at the beginning
    (*list)->head = new_node;

    return 0;
}

// the diagrafei me vasi kapoio stoixeio
int delete_node(List **list, void *data) {}

void print_list(List *list) {
    Node *current = list->head;

    while (current != NULL) {
        // printf("%s\n", current->data);
        current = current->next;
    }
}
