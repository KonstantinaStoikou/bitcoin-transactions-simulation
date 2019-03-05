#include "../include/transaction.h"
#include <stdio.h>

void print_transaction(void *data) {
    Transaction *t = (Transaction *)data;
    printf("%s %s %s %d", t->transaction_id, t->sender_wallet->wallet_id,
           t->receiver_wallet->wallet_id, t->value);
    char buffer[20];
    strftime(buffer, 20, "%d-%m-%Y %H:%M", t->date);
    printf("%s", buffer);
}