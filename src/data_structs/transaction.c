#include "../../include/data_structs/transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_transaction(void *data) {
    Transaction *t = (Transaction *)data;
    printf("%s %s %s %d ", t->transaction_id, t->sender_wallet->wallet_id,
           t->receiver_wallet->wallet_id, t->value);
    char buffer[20];
    strftime(buffer, 20, "%d-%m-%Y %H:%M", t->date);
    printf("%s", buffer);
}

int get_transaction_hash(void *wallet_id, int size) {
    char *w = (char *)wallet_id;
    return w[0] % size;
}

int get_transaction_id_hash(void *transaction_id) {
    char *t = (char *)transaction_id;
    return t[0] % TRANSACTION_HT_SIZE;
}

int check_transaction_id_only(void *data, void *transaction_id) {
    char *t = (char *)data;
    char *id = (char *)transaction_id;
    if (!strcmp(t, id)) {
        return 1;
    } else {
        return 0;
    }
}

int check_transaction_id(void *data, void *transaction_id) {
    Transaction *t = (Transaction *)data;
    char *id = (char *)transaction_id;
    if (!strcmp(t->transaction_id, id)) {
        return 1;
    } else {
        return 0;
    }
}

void delete_transaction(void **transaction) {
    free((Transaction *)(*transaction));
}