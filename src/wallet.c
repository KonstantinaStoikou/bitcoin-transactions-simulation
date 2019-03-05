#include "../include/wallet.h"
#include <stdio.h>
#include <string.h>
#include "../include/defines.h"

void print_wallet(void *wallet) {
    Wallet *w = (Wallet *)wallet;
    printf("WalletID: %s, Balance: $%d", w->wallet_id, w->balance);
}

int get_wallet_hash(void *wallet_id) {
    char *w = (char *)wallet_id;
    return w[0] % WALLET_HT_SIZE;
}

int check_wallet_id(void *data, void *wallet_id) {
    Wallet *w = (Wallet *)data;
    char *id = (char *)wallet_id;
    if (!strcmp(w->wallet_id, id)) {
        return 1;
    } else {
        return 0;
    }
}