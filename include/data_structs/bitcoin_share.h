#ifndef BITCOIN_SHARE_HEADER
#define BITCOIN_SHARE_HEADER

#include "bitcoin.h"

typedef struct Bitcoin_share {
    Bitcoin *bitcoin;
    int share;
} Bitcoin_share;

void print_bitcoin_share(void *data);
int check_bitcoin_share(void *data, void *bitcoin_id);

#endif