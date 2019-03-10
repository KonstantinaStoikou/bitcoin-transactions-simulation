#ifndef WALLET_HEADER
#define WALLET_HEADER

#include "../defines.h"
#include "../generic_structures/list.h"

typedef struct Wallet {
    char wallet_id[WALLET_ID_SIZE];
    int balance;
    // a list with bitcoin shares that this wallet owns
    List *bitcoins_list;
} Wallet;

void print_wallet(void *wallet);
int get_wallet_hash(void *wallet_id);
// Check if given wallet struct has given wallet_id value (argument 1: wallet
// struct, argument 2: wallet_id being search for) return 1 if same data, else 0
int check_wallet_id(void *data, void *wallet_id);
void delete_wallet(void **wallet);

#endif