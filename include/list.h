/**
 * A generic linked list
 *
 */

#ifndef LIST_HEADER
#define LIST_HEADER

// a node of the list
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// a pointer to the head of the list
typedef struct List {
    Node *head;
} List;

// Allocate memory for graph struct
List *initialize_list(void);
// Insert new node at the beginning of the list and return the newly added node
Node *add_node(List **list, void *data);
// Print all nodes of the list
void print_list(List *list);

#endif