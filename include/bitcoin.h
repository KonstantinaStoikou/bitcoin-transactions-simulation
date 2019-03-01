#ifndef BITCOIN_HEADER
#define BITCOINS_HEADER

#include "tree.h"

typedef struct Bitcoin {
    int bitcoin_id;
    // amount of initial value of bitcoin that has remained unspent
    int unspent;
    // number of transaction this bitcoin has participated in
    int num_of_transactions;
    // deiktis se dentro me bitcoin ids
    Tree *tree;
} Bitcoin;

void print_bitcoin(void *bitcoin);
int get_bitcoin_hash(void *bitcoin_id);

#endif