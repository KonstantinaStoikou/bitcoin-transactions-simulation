#ifndef TRANSACTION_HASHTABLE_DATA_HEADER
#define TRANSACTION_HASHTABLE_DATA_HEADER

#include "wallet.h"

// The transaction data stored in the sender/receiver hashtables
typedef struct Transaction_hashtable_data {
    Wallet *wallet;
    // a list with transactions that this wallet is either a sender or a
    // receiver
    List *transactions;
} Transaction_hashtable_data;

void print_transaction_hashtable_data(void *data);
// Check if given transaction hashtable data struct has given wallet_id value
// (argument 1: transaction hashtable data struct, argument 2: wallet_id being
// search for), return 1 if same data, else 0
int check_transaction_wallet(void *data, void *wallet_id);
void delete_transaction_hashtable_data(void **thd);

#endif