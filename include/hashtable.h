/**
 * A generic hash table with bucket hashing. A hashtable is a dynamic array of
 * lists of buckets, and buckets are dynamic generic arrays.
 *
 */

#ifndef HASHTABLE_HEADER
#define HASHTABLE_HEADER

#include "list.h"

// A dynamic generic array
typedef struct Bucket {
    void **data;
} Bucket;

// A pointer to a dynamic array with lists (pointers to heads of lists) of
// buckets
typedef struct Hashtable {
    List *table;
    int num_of_entries;
} Hashtable;

Hashtable *initialize_hashtable(int num_of_entries);

#endif