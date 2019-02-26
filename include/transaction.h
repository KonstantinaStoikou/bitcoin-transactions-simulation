#ifndef TRANSACTION_HEADER
#define TRANSACTION_HEADER

#include <time.h>

typedef struct Transaction {
    char *transaction_id;
    char *sender_wallet_id;
    char *receiver_wallet_id;
    int value;
    // a struct to store both time and date
    struct tm *date;
} Transaction;

#endif