#include "../include/bitcoin_tree_data.h"
#include <stdio.h>
#include "../include/transaction.h"

void print_bitcoin_tree_data(void *data) {
    Bitcoin_tree_data *btd = (Bitcoin_tree_data *)data;
    printf("%s %d", btd->wallet_id, btd->amount);
    if (btd->transaction != NULL) {
        printf("%s", btd->transaction->transaction_id);
    }
}

void print_bitcoin_transactions(void *data) {
    Bitcoin_tree_data *btd = (Bitcoin_tree_data *)data;
    if (btd->transaction != NULL) {
        print_transaction(btd->transaction);
    }
}