#include "../../include/main_functions/request_transaction_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_structs/transaction.h"
#include "../../include/data_structs/transaction_hashtable_data.h"
#include "../../include/data_structs/wallet.h"

void make_transaction(char *transaction_id, char *sender_wal_id,
                      char *receiver_wal_id, int value, char *date, char *time,
                      Hashtable **wallets, Hashtable **sender_ht,
                      Hashtable **receiver_ht) {
    // check if sender and receiver exist
    int pos = get_hash(get_wallet_hash, sender_wal_id);
    Wallet *sender_wal = (Wallet *)search_hashtable(wallets, pos, sender_wal_id,
                                                    check_wallet_id);
    if (sender_wal == NULL) {
        printf(RED "%s: There is no sender wallet with this id.\n\n" RESET,
               sender_wal_id);
        return;
    }
    pos = get_hash(get_wallet_hash, receiver_wal_id);
    Wallet *receiver_wal = (Wallet *)search_hashtable(
        wallets, pos, receiver_wal_id, check_wallet_id);
    if (receiver_wal == NULL) {
        printf(RED "%s: There is no receiver wallet with this id.\n\n" RESET,
               receiver_wal_id);
        return;
    }

    // check if sender has the amount of the transaction else return

    // first insert values into transaction struct and insert to hashtables then
    // break tree and point to these transactions

    // insert values into a transaction struct
    Transaction *transaction = malloc(sizeof(Transaction));
    strcpy(transaction->transaction_id, transaction_id);
    transaction->sender_wallet = sender_wal;
    transaction->receiver_wallet = receiver_wal;
    transaction->value = value;
    struct tm *tm_info = ascii_to_tm(date, time);
    transaction->date = tm_info;

    // insert transaction to both sender and receiver hashtables
    pos = get_transaction_hash(sender_wal_id, (*sender_ht)->num_of_entries);
    Transaction_hashtable_data *sender_thd =
        (Transaction_hashtable_data *)search_hashtable(
            sender_ht, pos, sender_wal_id, check_transaction_wallet);
    add_list_node(&sender_thd->transactions, transaction, sizeof(Transaction));
    pos = get_transaction_hash(receiver_wal_id, (*receiver_ht)->num_of_entries);
    Transaction_hashtable_data *receiver_thd =
        (Transaction_hashtable_data *)search_hashtable(
            receiver_ht, pos, receiver_wal_id, check_transaction_wallet);
    add_list_node(&receiver_thd->transactions, transaction,
                  sizeof(Transaction));

    free(transaction);
}

struct tm *ascii_to_tm(char *date_str, char *time_str) {
    struct tm *tm = malloc(sizeof(struct tm));
    char *date[3];  // maximum number of members of date is 3 (DD-MM-YYYY)
    int count = 0;
    char *d = strtok(date_str, "-");  // split prompt by spaces
    while (d) {
        date[count] = d;
        count++;
        d = strtok(NULL, "-");
    }
    char *time[2];  // maximum number of members of time is 2 (HH:MM)
    count = 0;
    char *t = strtok(time_str, ":");  // split prompt by spaces
    while (t) {
        time[count] = t;
        count++;
        t = strtok(NULL, ":");
    }

    tm->tm_mday = atoi(date[0]);
    tm->tm_mon = atoi(date[1]) - 1;
    tm->tm_year = atoi(date[2]) - 1900;
    tm->tm_hour = atoi(time[0]);
    tm->tm_min = atoi(time[1]);
    return tm;
}