#include "../include/read_functions.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitcoin.h"
#include "../include/bitcoin_share.h"
#include "../include/bitcoin_tree_data.h"
#include "../include/defines.h"
#include "../include/transaction.h"
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
                                Hashtable **wallets, Hashtable **bitcoins) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    // format path because of folder structure
    char filepath[strlen(filename) + 4];
    snprintf(filepath, sizeof(filepath), "%s%s", "./", filename);

    fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror(RED "Balances file cannot be opened" RESET);
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, fp) != -1) {
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
                free(bitc);
                // increase total balance of wallet by one full bitcoin value
                wal->balance += bitcoin_value;
            }
        }
        // add wallet struct to wallet hashtable
        int wpos = get_hash(get_wallet_hash, wal->wallet_id);
        insert_hashtable_entry(wallets, wpos, wal, sizeof(Wallet));
        free(wal);
    }
    printf("\n");
    fclose(fp);
}

int read_transaction_file(char *filename) {
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

    while (getline(&line, &len, fp) != -1) {
        printf("%s", line);

        char *words[6];  // maximum number of words for a line of that file is 6
        int count = 0;
        char *w = strtok(line, " ");  // split prompt by spaces
        while (w) {
            words[count] = w;
            printf("token #%d is : %s\n", count, words[count]);
            count++;
            w = strtok(NULL, " ");
        }
        // insert values into a transaction struct
        Transaction *transaction = malloc(sizeof(Transaction));
        strcpy(transaction->transaction_id, words[0]);
        // search in wallet hashtable for sender and receiver and point to them
        // strcpy(transaction->sender_wallet_id, words[1]);
        // strcpy(transaction->receiver_wallet_id, words[2]);
        transaction->value = atoi(words[3]);
        char buffer[26];
        struct tm *tm_info = ascii_to_tm(words[4], words[5]);

        strftime(buffer, 26, "%d-%m-%Y %H:%M", tm_info);
        puts(buffer);
    }
    printf("\n");
    fclose(fp);
}

struct tm *ascii_to_tm(char *date_str, char *time_str) {
    struct tm *tm;
    char *date[3];  // maximum number of members of date is 3 (DD-MM-YYYY)
    int count = 0;
    char *d = strtok(date_str, "-");  // split prompt by spaces
    while (d) {
        date[count] = d;
        printf("token #%d is : %s\n", count, date[count]);
        count++;
        d = strtok(NULL, "-");
    }
    char *time[2];  // maximum number of members of time is 2 (HH:MM)
    count = 0;
    char *t = strtok(time_str, ":");  // split prompt by spaces
    while (t) {
        time[count] = t;
        printf("token #%d is : %s\n", count, time[count]);
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
