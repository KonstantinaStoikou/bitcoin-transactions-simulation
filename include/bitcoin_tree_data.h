#ifndef BITCOIN_TREE_DATA_HEADER
#define BITCOIN_TREE_DATA_HEADER

#include "defines.h"
#include "transaction.h"

// The bitcoin data struct stored in the tree
typedef struct Bitcoin_tree_data {
    char wallet_id[WALLET_ID_SIZE];
    int amount;
    Transaction *transaction;
} Bitcoin_tree_data;

void print_bitcoin_tree_data(void *data);
void print_bitcoin_transactions(void *data);

#endif