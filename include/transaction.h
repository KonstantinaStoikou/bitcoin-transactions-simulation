#ifndef TRANSACTION_HEADER
#define TRANSACTION_HEADER

#include <time.h>
#include "defines.h"
#include "wallet.h"

typedef struct Transaction {
    char transaction_id[TRANSACTION_ID_SIZE];
    Wallet *sender_wallet;
    Wallet *receiver_wallet;
    int value;
    // a struct to store both time and date
    struct tm *date;
} Transaction;

void print_transaction(void *data);

#endif