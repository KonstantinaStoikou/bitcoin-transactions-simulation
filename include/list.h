/**
 * A generic linked list (using void* for data).
 *
 */

#ifndef LIST_HEADER
#define LIST_HEADER

// A node of the list
typedef struct List_node {
    void *data;
    struct List_node *next;
} List_node;

// A pointer to the head of the list
typedef struct List {
    List_node *head;
} List;

// Allocate memory for a new list struct and return it
List *initialize_list(void);
// Insert new node at the beginning of the list and return the newly added node
List_node *add_list_node(List **list, void *data);
// Delete a node with the given data, returns 1 if there was an error, else 0
int delete_list_node(List **list, void *data);
// Search for a node with the given data and return it
List_node *search_list_node(List **list, void *data);
// Search for the previous node of the node with the given data and return it
List_node *search_list_prev_node(List **list, void *data);
// Print all nodes of the list giving a printing function as argument depending
// on the data struct
void print_list(List *list, void (*fptr)(void *));
// Release memory of list giving a delete function as argument depending on the
// data struct
void delete_list(List **list, void (*fptr)(void *));

#endif