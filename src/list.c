#include "../include/list.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/defines.h"

List *initialize_list(void) {
    List *list = NULL;
    list = malloc(sizeof(List));
    list->head = NULL;

    return list;
}

List_node *add_list_node(List **list, void *data) {
    // Allocate memory for node
    List_node *new_node = (List_node *)malloc(sizeof(List_node));
    new_node->data = data;
    new_node->next = (*list)->head;
    // Change head pointer as new node is added at the beginning
    (*list)->head = new_node;

    return new_node;
}

int delete_list_node(List **list, void *data) {
    // check if node to be deleted is the head
    if ((*list)->head->data == data) {
        List_node *node_deleted = (*list)->head;
        (*list)->head = node_deleted->next;
        free(node_deleted);
        return 0;
    }

    // else continue
    // find the previous node of the one to be deleted
    List_node *prev = search_list_prev_node(list, data);
    if (prev == NULL) {
        perror(RED "The node does not exist in the list" RESET);
        return 1;
    }

    // link previous node with the next of the one to delete
    List_node *node_deleted = prev->next;
    prev->next = node_deleted->next;
    // free memory
    free(node_deleted);
    return 0;
}

List_node *search_list_node(List **list, void *data) {
    List_node *current = (*list)->head;

    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

List_node *search_list_prev_node(List **list, void *data) {
    List_node *current = (*list)->head;

    while (current != NULL && current->next != NULL) {
        if (current->next->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Give a printing function as argument depending on the data struct
void print_list(List *list, void (*fptr)(void *)) {
    List_node *current = list->head;

    while (current != NULL) {
        (*fptr)(current->data);
        printf("\n");
        current = current->next;
    }
}

void delete_list(List **list) {
    List_node *current = (*list)->head;

    while (current != NULL) {
        // free(current->data);
        free(current);
        current = current->next;
    }
    free(*list);
}