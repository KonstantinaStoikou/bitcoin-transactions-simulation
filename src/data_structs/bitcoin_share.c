#include "../../include/data_structs/bitcoin_share.h"
#include <stdio.h>

void print_bitcoin_share(void *data) {
    Bitcoin_share *b = (Bitcoin_share *)data;
    printf("BitcoinID: %d, Share: $%d", b->bitcoin->bitcoin_id, b->share);
}

int check_bitcoin_share(void *data, void *bitcoin_id) {
    Bitcoin_share *bcs = (Bitcoin_share *)data;
    int id = *(int *)bitcoin_id;
    if (bcs->bitcoin->bitcoin_id == id) {
        return 1;
    } else {
        return 0;
    }
}