/**
 * A generic hash table with bucket hashing. A hashtable is a dynamic array of
 * pointers to lists of buckets, and buckets are dynamic generic arrays.
 *
 */

#ifndef HASHTABLE_HEADER
#define HASHTABLE_HEADER

#include "list.h"

// A dynamic generic array
typedef struct Bucket {
    void **data;
    int num_of_entries;
    // mporei na min to xreiasto analogos to readme mou
    void *remaining_space;
} Bucket;

// A pointer to a dynamic array with pointers to lists of
// buckets
typedef struct Hashtable {
    List **table;
    int num_of_entries;
    int bucket_size;
} Hashtable;

// Allocate memory for hashtable and initialize table with the given number of
// entries
Hashtable *initialize_hashtable(int num_of_entries, int bucket_size);
// Allocate memory for bucket based on the given size in bytes and the size of
// the structs that will be passed as data
Bucket *initialize_bucket(int size, int sizeof_struct);
// Insert an element in the given position of the hashtable and return the
// inserted data
void *insert_hashtable_entry(Hashtable **ht, int position, void *data);

#endif