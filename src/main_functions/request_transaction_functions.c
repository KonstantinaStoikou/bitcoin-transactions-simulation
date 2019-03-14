#include "../../include/main_functions/request_transaction_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_structs/bitcoin_share.h"
#include "../../include/data_structs/bitcoin_tree_data.h"
#include "../../include/data_structs/transaction.h"
#include "../../include/data_structs/transaction_hashtable_data.h"
#include "../../include/data_structs/wallet.h"

void make_transaction(char *transaction_id, char *sender_wal_id,
                      char *receiver_wal_id, int value, char *date, char *time,
                      Hashtable **wallets, Hashtable **sender_ht,
                      Hashtable **receiver_ht, struct tm **recent_datetime) {
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

    // check if sender has the amount of the transaction in their balance
    if (sender_wal->balance < value) {
        printf(RED
               "%s: The balance in this wallet is not sufficient for the "
               "transaction.\n\n" RESET,
               sender_wal_id);
        return;
    }

    // if date was not given at all get current time
    struct tm *tm_info = NULL;
    if (date == NULL && time == NULL) {
        tm_info = get_current_time();
    } else {
        tm_info = ascii_to_tm(date, time);
        // datetime should be aftermost recent datetime but before or equal to
        // current time
        if (*recent_datetime != NULL &&
            (compare_datetime(tm_info, *recent_datetime) <= 0 ||
             compare_datetime(tm_info, get_current_time()) > 0)) {
            printf(RED "Invalid date and time.\n" RESET);
            return;
        }
    }

    *recent_datetime = tm_info;

    // insert values into a transaction struct
    Transaction *transaction = malloc(sizeof(Transaction));
    strcpy(transaction->transaction_id, transaction_id);
    transaction->sender_wallet = sender_wal;
    transaction->receiver_wallet = receiver_wal;
    transaction->value = value;
    transaction->date = tm_info;

    // insert transaction to both sender and receiver hashtables
    pos = get_transaction_hash(sender_wal_id, (*sender_ht)->num_of_entries);
    Transaction_hashtable_data *sender_thd =
        (Transaction_hashtable_data *)search_hashtable(
            sender_ht, pos, sender_wal_id, check_transaction_wallet);
    List_node *inserted_transaction = add_list_node(
        &sender_thd->transactions, transaction, sizeof(Transaction));
    pos = get_transaction_hash(receiver_wal_id, (*receiver_ht)->num_of_entries);
    Transaction_hashtable_data *receiver_thd =
        (Transaction_hashtable_data *)search_hashtable(
            receiver_ht, pos, receiver_wal_id, check_transaction_wallet);

    // Allocate memory for node (cannot use add_list_node because of memcpy)
    List_node *new_node = (List_node *)malloc(sizeof(List_node));
    new_node->data = malloc(sizeof(Transaction));
    memcpy(new_node->data, inserted_transaction->data, sizeof(Transaction));
    new_node->next = receiver_thd->transactions->head;
    // Change head pointer as new node is added at the beginning
    receiver_thd->transactions->head = new_node;

    free(transaction);
    // if tm_info points to malloc'ed space, free it
    if (date != NULL || time != NULL) {
        free(tm_info);
    }

    // decrease/increase balances
    sender_wal->balance -= value;
    receiver_wal->balance += value;

    // break tree and point to these transactions
    List_node *current_share = (List_node *)sender_wal->bitcoins_list->head;
    while (current_share != NULL && value != 0) {
        int old_value = value;  // store value before it is changed in tree
        List_node *next_share = current_share->next;
        Transaction *t = (Transaction *)inserted_transaction->data;
        Bitcoin_share *sender_share = (Bitcoin_share *)current_share->data;
        traverse_bitcoin_tree(sender_share->bitcoin->tree->root, &t, &value);
        sender_share->bitcoin->num_of_transactions++;
        sender_share->bitcoin->unspent -= old_value;
        if (sender_share->bitcoin->unspent < 0) {
            sender_share->bitcoin->unspent = 0;
        }

        // change share for sender
        sender_share->share -= (old_value - value);
        // if receiver didn't have bitcoin in list add it
        if (search_list_node(&receiver_wal->bitcoins_list,
                             &sender_share->bitcoin->bitcoin_id,
                             check_bitcoin_share) == NULL) {
            Bitcoin_share *new_bcs = malloc(sizeof(Bitcoin_share));
            new_bcs->share = old_value - value;
            new_bcs->bitcoin = sender_share->bitcoin;
            add_list_node(&receiver_wal->bitcoins_list, new_bcs,
                          sizeof(Bitcoin_share));
            free(new_bcs);
        }
        // if sender bitcoin share is zero remove it from bitcoin list of wallet
        if (sender_share->share == 0) {
            delete_list_node(&sender_wal->bitcoins_list,
                             &sender_share->bitcoin->bitcoin_id,
                             check_bitcoin_share);
        }

        current_share = next_share;
    }

    printf("Successful transaction.\n");
}

struct tm *ascii_to_tm(char *date_str, char *time_str) {
    struct tm *tm = malloc(sizeof(struct tm));
    char *date[3];  // maximum number of members of date is 3 (DD-MM-YYYY)
    int count = 0;
    char *d = strtok(date_str, "-");
    while (d) {
        date[count] = d;
        count++;
        d = strtok(NULL, "-");
    }
    char *time[2];  // maximum number of members of time is 2 (HH:MM)
    count = 0;
    char *t = strtok(time_str, ":");
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
    tm->tm_sec = 0;

    return tm;
}

void traverse_bitcoin_tree(Tree_node *node, Transaction **transaction,
                           int *value) {
    if (node == NULL) {
        return;
    }

    // check if this node is a leaf (check either sender or receiver if null)
    if (node->sender == NULL) {
        // check if wallet id is the same as the sender of this transaction and
        // node has money
        Bitcoin_tree_data *btd = (Bitcoin_tree_data *)node->data;
        if (!strcmp(btd->wallet_id, (*transaction)->sender_wallet->wallet_id) &&
            btd->amount != 0) {
            // create new node data for sender and receiver
            Bitcoin_tree_data *new_sender_btd =
                malloc(sizeof(Bitcoin_tree_data));
            strcpy(new_sender_btd->wallet_id,
                   (*transaction)->sender_wallet->wallet_id);
            new_sender_btd->transaction = *transaction;
            if (btd->amount > *value) {
                new_sender_btd->amount = btd->amount - *value;
                *value = 0;
            } else {
                new_sender_btd->amount = 0;
                *value -= btd->amount;
            }
            Bitcoin_tree_data *new_receiver_btd =
                malloc(sizeof(Bitcoin_tree_data));
            strcpy(new_receiver_btd->wallet_id,
                   (*transaction)->receiver_wallet->wallet_id);
            new_receiver_btd->transaction = *transaction;
            new_receiver_btd->amount = btd->amount - new_sender_btd->amount;
            // add nodes to tree
            add_sender(node, new_sender_btd, sizeof(Bitcoin_tree_data));
            add_receiver(node, new_receiver_btd, sizeof(Bitcoin_tree_data));
            free(new_sender_btd);
            free(new_receiver_btd);
        }
        return;
    }

    traverse_bitcoin_tree(node->sender, transaction, value);
    traverse_bitcoin_tree(node->receiver, transaction, value);
}

int compare_datetime(struct tm *transaction_date, struct tm *comparison_date) {
    time_t t1 = mktime(transaction_date);
    time_t t2 = mktime(comparison_date);
    return difftime(t1, t2);
}

struct tm *get_current_time() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return timeinfo;
}