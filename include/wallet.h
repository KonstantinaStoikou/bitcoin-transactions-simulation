#ifndef WALLET_HEADER
#define WALLET_HEADER

#include "defines.h"
#include "list.h"

typedef struct Wallet {
    char wallet_id[WALLET_ID_SIZE];
    int balance;
    List *bitcoins_list;
} Wallet;

void print_wallet(void *wallet);
int get_wallet_hash(void *wallet_id);

#endif