#include "../include/read_functions.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
                                Hashtable **wallets) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    // format path because of folder structure
    char filepath[strlen(filename) + 4];
    snprintf(filepath, sizeof(filepath), "%s%s", "./", filename);

    fp = fopen(filepath, "r");
    printf("file is %s\n", filepath);
    if (fp == NULL) {
        perror(RED "Balances file cannot be opened" RESET);
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, fp) != -1) {
        Wallet *wal = malloc(sizeof(Wallet));
        printf("%s", line);

        char *word = strtok(line, " ");
        strcpy(wal->wallet_id, word);
        printf("username is : %s\n", wal->wallet_id);
        wal->balance = 0;
        while (word) {
            word = strtok(NULL, " ");
            if (word) {
                printf("bitcoin is : %s\n", word);
                wal->balance += bitcoin_value;
            }
        }
        int pos = get_hash(get_wallet_hash, wal->wallet_id);
        insert_hashtable_entry(wallets, pos, wal, sizeof(Wallet));
        free(wal);
    }
    printf("\n");
    fclose(fp);
}

void read_transaction_file(char *filename) {
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
        transaction->transaction_id = malloc(sizeof(words[0]));
        strcpy(transaction->transaction_id, words[0]);
        transaction->sender_wallet_id = malloc(sizeof(words[1]));
        strcpy(transaction->sender_wallet_id, words[1]);
        transaction->receiver_wallet_id = malloc(sizeof(words[2]));
        strcpy(transaction->receiver_wallet_id, words[2]);
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
