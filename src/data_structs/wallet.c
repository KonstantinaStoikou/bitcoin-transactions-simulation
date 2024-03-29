#include "../../include/data_structs/wallet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/defines.h"

void print_wallet(void *wallet) {
    Wallet *w = (Wallet *)wallet;
    printf("WalletID: %s, Balance: $%d", w->wallet_id, w->balance);
}

int get_wallet_hash(void *wallet_id) {
    char *w = (char *)wallet_id;
    unsigned long hash = 5381;
    int c;

    while ((c = *w++)) {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }

    return hash % WALLET_HT_SIZE;
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

void delete_wallet(void **wallet) {
    // will delete list of bitcoin shares, but not the actual bitcoins it points
    // to
    delete_list(&((Wallet *)(*wallet))->bitcoins_list, NULL);
    free((Wallet *)(*wallet));
}