#include "../include/bitcoin_tree_data.h"
#include <stdio.h>

void print_bitcoin_tree_data(void *data) {
    Bitcoin_tree_data *btd = (Bitcoin_tree_data *)data;
    printf("%s %s %s %d", btd->transaction->transaction_id,
           btd->transaction->sender_wallet_id,
           btd->transaction->receiver_wallet_id, btd->transaction->value);
    char buffer[20];
    strftime(buffer, 20, "%d-%m-%Y %H:%M", btd->transaction->date);
    printf("%s", buffer);
}