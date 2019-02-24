#ifndef TRANSACTION_HEADER
#define TRANSACTION_HEADER

typedef struct Transaction {
    char *transaction_id;
    char *wallet_id;
    int bitcoin_id;
    int value;
    char *date;
    char *time;
} Transaction;

#endif