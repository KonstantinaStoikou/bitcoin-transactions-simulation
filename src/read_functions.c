#include "../include/read_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitcoin.h"
#include "../include/bitcoin_share.h"
#include "../include/bitcoin_tree_data.h"
#include "../include/defines.h"
#include "../include/request_transaction_functions.h"
#include "../include/transaction.h"
#include "../include/transaction_hashtable_data.h"
#include "../include/wallet.h"

void read_arguments(int argc, char const *argv[], char **bitcoin_balances_file,
                    char **transaction_file, int *bitcoin_value,
                    int *sender_hashtable_num_of_entries,
                    int *receiver_hashtable_num_of_entries, int *bucket_size) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            *bitcoin_balances_file = malloc(strlen(argv[i + 1]) + 1);
            strcpy(*bitcoin_balances_file, argv[i + 1]);
        } else if (strcmp(argv[i], "-t") == 0) {
            *transaction_file = malloc(strlen(argv[i + 1]) + 1);
            strcpy(*transaction_file, argv[i + 1]);
        } else if (strcmp(argv[i], "-v") == 0) {
            *bitcoin_value = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-h1") == 0) {
            *sender_hashtable_num_of_entries = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-h2") == 0) {
            *receiver_hashtable_num_of_entries = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-b") == 0) {
            *bucket_size = atoi(argv[i + 1]);
        }
    }
}

void read_bitcoin_balances_file(char *filename, int bitcoin_value,
                                Hashtable **wallets, Hashtable **bitcoins,
                                Hashtable **sender_ht,
                                Hashtable **receiver_ht) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    // format path because of folder structure
    char filepath[strlen(filename) + 3];
    snprintf(filepath, sizeof(filepath), "%s%s", "./", filename);

    fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror(RED "Balances file cannot be opened" RESET);
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, fp) != -1) {
        // remove newline character from line
        line[strcspn(line, "\r\n")] = 0;
        char *word = strtok(line, " ");
        // initialize wallet struct
        Wallet *wal = malloc(sizeof(Wallet));
        strcpy(wal->wallet_id, word);
        wal->balance = 0;
        wal->bitcoins_list = initialize_list();
        while (word) {
            word = strtok(NULL, " ");
            if (word) {
                // initialize bitcoin share struct
                Bitcoin_share *bitc_share = malloc(sizeof(Bitcoin_share));
                // initialize bitcoin struct
                Bitcoin *bitc = malloc(sizeof(Bitcoin));
                bitc->bitcoin_id = atoi(word);
                bitc->unspent = bitcoin_value;
                bitc->num_of_transactions = 0;
                bitc->tree = initialize_tree();
                // initialize bitcoin tree data struct
                Bitcoin_tree_data *btd = malloc(sizeof(Bitcoin_tree_data));
                btd->amount = bitcoin_value;
                btd->transaction = NULL;
                strcpy(btd->wallet_id, wal->wallet_id);
                // add bitcoin tree data struct to bitcoin tree
                bitc->tree->root =
                    allocate_tree_node(btd, sizeof(Bitcoin_tree_data));
                // add bitcoin struct to bitcoin hashtable and make bitcoin
                // share point to it
                int bpos = get_hash(get_bitcoin_hash, &bitc->bitcoin_id);
                bitc_share->bitcoin = insert_hashtable_entry(
                    bitcoins, bpos, bitc, sizeof(Bitcoin));
                bitc_share->share = bitcoin_value;
                add_list_node(&wal->bitcoins_list, bitc_share,
                              sizeof(Bitcoin_share));
                free(btd);
                free(bitc->tree->root->data);
                free(bitc->tree->root);
                free(bitc->tree);
                free(bitc);
                free(bitc_share);
                // increase total balance of wallet by one full bitcoin value
                wal->balance += bitcoin_value;
            }
        }
        // add wallet struct to wallet hashtable
        int wpos = get_hash(get_wallet_hash, wal->wallet_id);
        Wallet *inserted_wal = (Wallet *)insert_hashtable_entry(
            wallets, wpos, wal, sizeof(Wallet));

        // initialize transaction hashtable data for sender and receiver
        // hashtables for this wallet
        List *sender_t_list = initialize_list();
        List *receiver_t_list = initialize_list();
        Transaction_hashtable_data *sender_thd =
            malloc(sizeof(Transaction_hashtable_data));
        Transaction_hashtable_data *receiver_thd =
            malloc(sizeof(Transaction_hashtable_data));
        sender_thd->wallet = inserted_wal;
        sender_thd->transactions = sender_t_list;
        receiver_thd->wallet = inserted_wal;
        receiver_thd->transactions = receiver_t_list;

        // insert transaction hashtable data in sender/receiver hashtables
        int tpos =
            get_transaction_hash(wal->wallet_id, (*sender_ht)->num_of_entries);
        insert_hashtable_entry(sender_ht, tpos, sender_thd,
                               sizeof(Transaction_hashtable_data));
        tpos = get_transaction_hash(wal->wallet_id,
                                    (*receiver_ht)->num_of_entries);
        insert_hashtable_entry(receiver_ht, tpos, receiver_thd,
                               sizeof(Transaction_hashtable_data));
        free(wal);
        free(sender_thd);
        free(receiver_thd);
    }
    printf("\n");
    free(line);
    fclose(fp);
}

int read_transaction_file(char *filename, Hashtable **sender_ht,
                          Hashtable **receiver_ht, Hashtable **wallets) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    // format path because of folder structure
    char filepath[strlen(filename) + 3];
    snprintf(filepath, sizeof(filepath), "%s%s", "./", filename);

    fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror(RED "Transactions file cannot be opened" RESET);
        exit(EXIT_FAILURE);
    }

    // create a hashtable to store transaction ids (and use transaction id as
    // key) to check easily if a given transaction id is unique
    Hashtable *transaction_ids =
        initialize_hashtable(TRANSACTION_HT_SIZE, TRANSACTION_BUCKET_SIZE);

    int pos;  // variable to store positions found for hashtables

    while (getline(&line, &len, fp) != -1) {
        // remove newline character from line
        line[strcspn(line, "\r\n")] = 0;
        // input format: id sender receiver amount date time
        char *words[6];  // maximum number of words for a line of that file is 6
        int count = 0;
        char *w = strtok(line, " ");  // split prompt by spaces
        while (w) {
            words[count] = w;
            count++;
            w = strtok(NULL, " ");
        }
        char *tr_id = words[0];
        // check if transaction id already exists (in hashtable), else add it to
        // hashtable
        pos = get_hash(get_transaction_id_hash, tr_id);
        char *tr_id_stored = (char *)search_hashtable(
            &transaction_ids, pos, tr_id, check_transaction_id_only);
        if (tr_id_stored == NULL) {
            make_transaction(tr_id, words[1], words[2], atoi(words[3]),
                             words[4], words[5], wallets, sender_ht,
                             receiver_ht);
            insert_hashtable_entry(&transaction_ids, pos, tr_id,
                                   sizeof(char *));
        } else {
            printf(RED "Transaction with id: %s already exists.\n" RESET,
                   tr_id);
        }
    }
    delete_hashtable(&transaction_ids, NULL);
    printf("\n");
    free(line);
    fclose(fp);
    return NULL;
}
