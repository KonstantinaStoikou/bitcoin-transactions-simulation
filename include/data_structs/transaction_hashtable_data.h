/**
 * A struct and it's functions to store wallet pointer and a list of
 * transactions for this wallet (depending on hashtable that are stored in, the
 * list of transactions has transactions that wallet is either sender or
 * receiver of these). This struct is stored in the sender/receiver hashtables.
 *
 */

#ifndef TRANSACTION_HASHTABLE_DATA_HEADER
#define TRANSACTION_HASHTABLE_DATA_HEADER

#include "wallet.h"

typedef struct Transaction_hashtable_data {
    Wallet *wallet;
    // a list with transactions that this wallet is either a sender or a
    // receiver
    List *transactions;
} Transaction_hashtable_data;

void print_transaction_hashtable_data(void *data);
// Check if given transaction hashtable data struct has given wallet_id value
// (argument 1: transaction hashtable data struct, argument 2: wallet_id being
// search for), return 1 if same data, else return 0
int check_transaction_wallet(void *data, void *wallet_id);
// Delete list of transactions and transactions from hashtable
void delete_transaction_hashtable_data(void **thd);
// Delete only list of transactions from hashtable (because the transactions it
// points to, are already deleted)
void delete_transaction_hashtable_data_pointers(void **thd);

#endif