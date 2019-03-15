/**
 * A struct and it's functions to store bitcoin pointer and the share that
 * someone has of this particular bitcoin.
 *
 */

#ifndef BITCOIN_SHARE_HEADER
#define BITCOIN_SHARE_HEADER

#include "bitcoin.h"

typedef struct Bitcoin_share {
    Bitcoin *bitcoin;
    int share;
} Bitcoin_share;

void print_bitcoin_share(void *data);
// Check if given bitcoin share struct has given bitcoin_id value (argument 1:
// bitcoin share struct, argument 2: bitcoin_id being search for) return 1 if
// same data, else return 0
int check_bitcoin_share(void *data, void *bitcoin_id);

#endif