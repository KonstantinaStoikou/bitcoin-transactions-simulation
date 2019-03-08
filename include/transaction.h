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
// Find position of a wallet's transactions in the hashtable array with wallet
// id as key
int get_transaction_hash(void *wallet_id, int size);
// Find position of a transaction id in the hashtable array with transaction id
// as key
int get_transaction_id_hash(void *transaction_id);
// Check for transactions id hashtable only
int check_transaction_id_only(void *data, void *transaction_id);
int check_transaction_id(void *data, void *transaction_id);

#endif