#ifndef TRANSACTION_HEADER
#define TRANSACTION_HEADER

typedef struct Transaction {
    char *transaction_id;
    char *sender_wallet_id;
    char *receiver_wallet_id;
    int value;
    char *date;
    char *time;
} Transaction;

#endif