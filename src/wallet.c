#include "../include/wallet.h"
#include <stdio.h>
#include "../include/defines.h"

void print_wallet(void *wallet) {
    Wallet *w = (Wallet *)wallet;
    printf("WalletID: %s, Balance: $%d", w->wallet_id, w->balance);
}

int get_wallet_hash(void *wallet_id) {
    char *w = (char *)wallet_id;
    return w[0] % WALLET_HT_SIZE;
}