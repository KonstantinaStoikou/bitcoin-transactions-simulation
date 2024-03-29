/**
 * A struct and it's functions to store bitcoin info.
 *
 */

#ifndef BITCOIN_HEADER
#define BITCOIN_HEADER

#include "../generic_structures/tree.h"

typedef struct Bitcoin {
    int bitcoin_id;
    // amount of initial value of bitcoin that has remained unspent
    int unspent;
    // number of transaction this bitcoin has participated in
    int num_of_transactions;
    Tree *tree;
} Bitcoin;

void print_bitcoin(void *bitcoin);
int get_bitcoin_hash(void *bitcoin_id);
// Check if given bitcoin struct has given bitcoin_id value (argument 1: bitcoin
// struct, argument 2: bitcoin_id being search for) return 1 if same data, else
// return 0
int check_bitcoin_id(void *data, void *bitcoin_id);
// Delete bitcoin tree
void delete_bitcoin(void **bitcoin);

#endif