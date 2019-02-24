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
int delete_node(List **list, void *data) {
    // check if node to be deleted is the head
    if ((*list)->head->data == data) {
    }

    // else continue
    // find the previous node of the one to be deleted
    Node *prev = search_for_previous_node(list, data);
    if (prev == NULL) {
        perror("The node does not exist in the list");
        return 1;
    }

    // free(temp);  // Free memory
}

Node *search_for_node(List **list, void *data) {
    Node *current = (*list)->head;

    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node *search_for_previous_node(List **list, void *data) {
    Node *current = (*list)->head;

    while (current != NULL && current->next != NULL) {
        if (current->next->data == data) {
            return current;
        }

        current = current->next;
    }
    return NULL;
}

void print_list(List *list) {
    Node *current = list->head;

    while (current != NULL) {
        // printf("%s\n", current->data);
        current = current->next;
    }
}
