/**
 * A struct and it's functions to store a wallet id, the amount of money that
 * were received or sent from this wallet and a pointer to the corresponding
 * transaction. This struct is stored in the nodes of the bitcoin tree.
 *
 */

#ifndef BITCOIN_TREE_DATA_HEADER
#define BITCOIN_TREE_DATA_HEADER

#include "../defines.h"
#include "transaction.h"

typedef struct Bitcoin_tree_data {
    char wallet_id[WALLET_ID_SIZE];
    int amount;
    Transaction *transaction;
} Bitcoin_tree_data;

void print_bitcoin_tree_data(void *data);
void print_bitcoin_transaction(void *data);

#endif