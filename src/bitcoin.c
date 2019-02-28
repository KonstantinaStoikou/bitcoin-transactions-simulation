#include "../include/bitcoin.h"
#include <stdio.h>
#include "../include/defines.h"

void print_bitcoin(void *bitcoin) {
    Bitcoin *b = (Bitcoin *)bitcoin;
    printf("BitcoinID: %d, Unspent: $%d, Number of transactions: %d",
           b->bitcoin_id, b->unspent, b->num_of_transactions);
}

int get_bitcoin_hash(void *bitcoin_id) {
    int b = *(int *)bitcoin_id;
    return b % BITCOIN_HT_SIZE;
}