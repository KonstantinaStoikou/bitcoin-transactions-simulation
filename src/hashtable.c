#include "../include/hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/defines.h"

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

int get_hash(int (*function)(void *), void *data) { return (*function)(data); }

Bucket *initialize_bucket(int size, int sizeof_struct) {
    // allocate memory for bucket struct (size in bytes given as argument)
    Bucket *buck = malloc(sizeof(Bucket));
    buck->num_of_entries = (size - sizeof(Bucket)) / sizeof_struct;
    buck->data = malloc(sizeof_struct * buck->num_of_entries);
    for (int i = 0; i < buck->num_of_entries; i++) {
        buck->data[i] = NULL;
    }
    // allocate remaining space in bucket so that:
    // bucket size + size of data array = given size in bytes
    buck->remaining_space = malloc((size - sizeof(Bucket)) % sizeof_struct);

    return buck;
}

void *insert_hashtable_entry(Hashtable **ht, int position, void *data,
                             int sizeof_data_struct) {
    List_node *bucket_node;
    // if there is no bucket in this position, add one
    if ((*ht)->table[position]->head == NULL) {
        Bucket *buck =
            initialize_bucket((*ht)->bucket_size, sizeof_data_struct);
        bucket_node =
            add_list_node(&((*ht)->table[position]), buck, sizeof(Bucket));
        free(buck);
    } else {
        bucket_node = (*ht)->table[position]->head;
    }

    // search bucket list to find an empty space in the buckets
    while (bucket_node != NULL) {
        // cast data of bucket list to Bucket, to access the Bucket data
        Bucket *buck = (Bucket *)bucket_node->data;
        // search bucket array for an empty space to insert new data
        for (int i = 0; i < buck->num_of_entries; i++) {
            if (buck->data[i] == NULL) {
                buck->data[i] = malloc(sizeof_data_struct);
                memcpy(buck->data[i], data, sizeof_data_struct);
                return buck->data[i];
            }
        }
        bucket_node = bucket_node->next;
    }
    // if no space was found, add a new bucket in the list and add the data
    // there
    Bucket *buck = initialize_bucket((*ht)->bucket_size, sizeof_data_struct);
    buck->data[0] = malloc(sizeof_data_struct);
    memcpy(buck->data[0], data, sizeof_data_struct);
    bucket_node =
        add_list_node(&((*ht)->table[position]), buck, sizeof(Bucket));
    free(buck);
    return ((Bucket *)bucket_node->data)->data[0];
}

void *search_hashtable(Hashtable **ht, int pos, void *data,
                       int (*function)(void *, void *)) {
    List_node *bucket_node = (*ht)->table[pos]->head;
    while (bucket_node != NULL) {
        Bucket *buck = (Bucket *)bucket_node->data;
        for (int i = 0; i < buck->num_of_entries; i++) {
            if (buck->data[i] != NULL) {
                if ((*function)(buck->data[i], data) == 1) {
                    return buck->data[i];
                }
            }
        }
        bucket_node = bucket_node->next;
    }
    return NULL;
}

void print_hashtable(Hashtable *ht, void (*function)(void *)) {
    for (int i = 0; i < ht->num_of_entries; i++) {
        printf(GREEN "- In hashtable entry %d: \n" RESET, i);
        List_node *current_entry = ht->table[i]->head;
        int count = 0;
        while (current_entry != NULL) {
            printf(BLUE "\tIn bucket %d: \n", count);
            Bucket *current_bucket = (Bucket *)current_entry->data;
            for (int i = 0; i < current_bucket->num_of_entries; i++) {
                if (current_bucket->data[i] == NULL) {
                    break;
                }
                printf(RESET "\t\t");
                // call print function given as argument
                (*function)(current_bucket->data[i]);
                printf("\n");
            }
            current_entry = current_entry->next;
            count++;
        }
    }
}

void delete_hashtable(Hashtable **ht, void (*function)(void **)) {
    for (int i = 0; i < (*ht)->num_of_entries; i++) {
        List_node *current = (*ht)->table[i]->head;
        List_node *next;

        while (current != NULL) {
            next = current->next;
            // delete bucket data
            Bucket *bucket = (Bucket *)current->data;
            for (int j = 0; j < bucket->num_of_entries; j++) {
                if (bucket->data[j] != NULL) {
                    if (*function != NULL) {
                        (*function)(&bucket->data[j]);
                    } else {
                        free(bucket->data[j]);
                    }
                }
            }
            // delete bucket
            free(bucket->remaining_space);
            free(bucket->data);
            free(bucket);
            // delete list node
            free(current);
            current = next;
        }
        free((*ht)->table[i]);
    }
    free((*ht)->table);
    free(*ht);
}
