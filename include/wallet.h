#ifndef WALLET_HEADER
#define WALLET_HEADER

typedef struct Wallet {
    char wallet_id[50];
    int balance;
    // deiktis se lista me bitcoin ids(i me deiktes se bticoins) (giati thelo na
    // exo to ipoloipo gia kathe xristi)
} Wallet;

void print_wallet(void *wallet);
int get_wallet_hash(void *wallet_id);

#endif