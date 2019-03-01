#ifndef WALLET_HEADER
#define WALLET_HEADER

#include "defines.h"

typedef struct Wallet {
    char wallet_id[WALLET_ID_SIZE];
    int balance;
    // deiktis se lista me bitcoin ids(i me deiktes se bticoins) (giati thelo na
    // exo to ipoloipo gia kathe xristi)
} Wallet;

void print_wallet(void *wallet);
int get_wallet_hash(void *wallet_id);

#endif