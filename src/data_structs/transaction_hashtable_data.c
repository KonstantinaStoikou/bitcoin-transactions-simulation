#include "../../include/data_structs/transaction_hashtable_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_structs/transaction.h"
#include "../../include/generic_structures/list.h"

void print_transaction_hashtable_data(void *data) {
    Transaction_hashtable_data *thd = (Transaction_hashtable_data *)data;
    printf("%s: \n", thd->wallet->wallet_id);
    print_list(thd->transactions, print_transaction);
}

int check_transaction_wallet(void *data, void *wallet_id) {
    Transaction_hashtable_data *thd = (Transaction_hashtable_data *)data;
    char *id = (char *)wallet_id;
    if (!strcmp(thd->wallet->wallet_id, id)) {
        return 1;
    } else {
        return 0;
    }
}

void delete_transaction_hashtable_data(void **thd) {
    delete_list(&((Transaction_hashtable_data *)(*thd))->transactions,
                delete_transaction);
    free(((Transaction_hashtable_data *)(*thd)));
}
