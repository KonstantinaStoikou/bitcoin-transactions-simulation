#include "../../include/data_structs/bitcoin_share.h"
#include <stdio.h>

void print_bitcoin_share(void *data) {
    Bitcoin_share *b = (Bitcoin_share *)data;
    printf("BitcoinID: %d, Share: $%d", b->bitcoin->bitcoin_id, b->share);
}