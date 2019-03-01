#ifndef TRANSACTION_HEADER
#define TRANSACTION_HEADER

#include <time.h>
#include "defines.h"

typedef struct Transaction {
    char transaction_id[TRANSACTION_ID_SIZE];
    char sender_wallet_id[WALLET_ID_SIZE];
    char receiver_wallet_id[WALLET_ID_SIZE];
    int value;
    // a struct to store both time and date
    struct tm *date;
} Transaction;

void print_transaction(void *data);

#endif