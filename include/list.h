/**
 * A generic linked list
 *
 */

#ifndef LIST_HEADER
#define LIST_HEADER

// A node of the list
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// A pointer to the head of the list
typedef struct List {
    Node *head;
} List;

// Allocate memory for graph struct
List *initialize_list(void);
// Insert new node at the beginning of the list and return the newly added node
Node *add_node(List **list, void *data);
// Delete a node with the given data, returns 1 if there was an error, else 0
int delete_node(List **list, void *data);
// Search for a node with the given data
Node *search_for_node(List **list, void *data);
// Search for the previous node of the node with the given data
Node *search_for_previous_node(List **list, void *data);
// Print all nodes of the list
void print_list(List *list);
// Release memory of list
void delete_list(List **list);

#endif