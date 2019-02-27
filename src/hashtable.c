#include "../include/hashtable.h"
#include <stdio.h>
#include <stdlib.h>

Hashtable *initialize_hashtable(int num_of_entries) {
    // allocate memory for hashtable struct
    Hashtable *ht = malloc(sizeof(Hashtable));
    ht->num_of_entries = num_of_entries;
    // allocate memory for array of lists
    ht->table = malloc(sizeof(List) * num_of_entries);
    // allocate memory for each list of the table
    for (int i = 0; i < num_of_entries; i++) {
        ht->table[i] = *initialize_list();
    }

    printf("size of list is %ld\n", sizeof(List));
    return ht;
}
