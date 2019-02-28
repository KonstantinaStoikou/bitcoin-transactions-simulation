#include "../include/hashtable.h"
#include <stdio.h>
#include <stdlib.h>

Hashtable *initialize_hashtable(int num_of_entries, int bucket_size) {
    // allocate memory for hashtable struct
    Hashtable *ht = malloc(sizeof(Hashtable));
    ht->num_of_entries = num_of_entries;
    ht->bucket_size = bucket_size;
    // allocate memory for array of lists
    ht->table = malloc(sizeof(List *) * num_of_entries);
    // allocate memory for each list of the table
    for (int i = 0; i < num_of_entries; i++) {
        ht->table[i] = initialize_list();
    }

    return ht;
}

Bucket *initialize_bucket(int size, int sizeof_struct) {
    // allocate memory for bucket struct (size in bytes given as argument)
    Bucket *buck = malloc(sizeof(Bucket));
    buck->num_of_entries = (size - sizeof(Bucket)) / sizeof_struct;
    buck->data = malloc(sizeof_struct * buck->num_of_entries);
    // allocate remaining space in bucket so that:
    // bucket size + size of data array = given size in bytes
    buck->remaining_space = malloc((size - sizeof(Bucket)) % sizeof_struct);

    return buck;
}

void *insert_hashtable_entry(Hashtable **ht, int position, void *data) {
    List_node *bucket_node;
    // if there is no bucket in this position, add one
    if ((*ht)->table[position]->head == NULL) {
        Bucket *buck = initialize_bucket((*ht)->bucket_size, sizeof(Bucket));
        bucket_node = add_list_node(&((*ht)->table[position]), buck);
    } else {
        bucket_node = (*ht)->table[position]->head;
    }

    // search bucket list to find an empty space in the buckets
    while (bucket_node->next != NULL) {
        // cast data of bucket list to Bucket, to access the Bucket data
        Bucket *buck = (Bucket *)bucket_node->data;
        // search bucket array for an empty space to insert new data
        for (int i = 0; i < buck->num_of_entries - 1; i++) {
            if (buck->data[i] == NULL) {
                buck->data[i] = data;
                return buck->data[i];
            }
        }
        bucket_node = bucket_node->next;
    }
    // if no space was found, add a new bucket in the list and add the data
    // there
    Bucket *buck = initialize_bucket((*ht)->bucket_size, sizeof(Bucket));
    buck->data[0] = data;
    bucket_node = add_list_node(&((*ht)->table[position]), buck);
    return buck->data[0];
}