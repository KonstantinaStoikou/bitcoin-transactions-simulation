#include "../../include/data_structs/bitcoin_tree_data.h"
#include <stdio.h>
#include "../../include/data_structs/transaction.h"

void print_bitcoin_tree_data(void *data) {
    Bitcoin_tree_data *btd = (Bitcoin_tree_data *)data;
    printf("Wallet: %s, Share: %d", btd->wallet_id, btd->amount);
    // check if not root node (because root does not point in any transaction)
    if (btd->transaction != NULL) {
        printf(", Transaction: %s", btd->transaction->transaction_id);
    }
}

void print_bitcoin_transactions(void *data) {
    Bitcoin_tree_data *btd = (Bitcoin_tree_data *)data;
    if (btd->transaction != NULL) {
        print_transaction(btd->transaction);
    }
}