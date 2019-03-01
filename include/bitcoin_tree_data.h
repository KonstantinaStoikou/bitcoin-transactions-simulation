#ifndef BITCOIN_TREE_DATA_HEADER
#define BITCOIN_TREE_DATA_HEADER

#include "transaction.h"

// The bitcoin data struct stored in the tree
typedef struct Bitcoin_tree_data {
    char *wallet_id;
    int amount;
    Transaction *transaction;
} Bitcoin_tree_data;

void print_bitcoin_tree_data(void *data);

#endif