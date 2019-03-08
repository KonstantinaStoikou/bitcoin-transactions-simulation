#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitcoin.h"
#include "../include/defines.h"
#include "../include/hashtable.h"
#include "../include/prompts.h"
#include "../include/read_functions.h"
#include "../include/wallet.h"

int main(int argc, char const *argv[]) {
    char *bitcoin_balances_file, *transaction_file;
    int bitcoin_value, sender_hashtable_num_of_entries,
        receiver_hashtable_num_of_entries, bucket_size;
    read_arguments(argc, argv, &bitcoin_balances_file, &transaction_file,
                   &bitcoin_value, &sender_hashtable_num_of_entries,
                   &receiver_hashtable_num_of_entries, &bucket_size);

    if (argc == 1) {
        bitcoin_balances_file =
            malloc(strlen("files/bitCoinBalancesFile.txt") + 1);
        strcpy(bitcoin_balances_file, "files/bitCoinBalancesFile.txt");
        transaction_file = malloc(strlen("files/transactionsFile.txt") + 1);
        strcpy(transaction_file, "files/transactionsFile.txt");
        bitcoin_value = 50;
        sender_hashtable_num_of_entries = 10;
        receiver_hashtable_num_of_entries = 15;
        bucket_size = 100;
    }

    printf(MAGENTA "bitcoin_balances_file:             %s\n",
           bitcoin_balances_file);
    printf("transaction_file:                  %s\n", transaction_file);
    printf("bitcoin_value:                     %d\n", bitcoin_value);
    printf("sender_hashtanewline character linuxble_num_of_entries:   %d\n",
           sender_hashtable_num_of_entries);
    printf("receiver_hashnewline character linuxtable_num_of_entries: %d\n",
           receiver_hashtable_num_of_entries);
    printf("bucket_size:                       %d\n" RESET, bucket_size);

    // initialize structs that will store data later
    Hashtable *wallets_ht =
        initialize_hashtable(WALLET_HT_SIZE, WALLET_BUCKET_SIZE);
    Hashtable *bitcoins_ht =
        initialize_hashtable(BITCOIN_HT_SIZE, BITCOIN_BUCKET_SIZE);
    Hashtable *sender_ht =
        initialize_hashtable(sender_hashtable_num_of_entries, bucket_size);
    Hashtable *receiver_ht =
        initialize_hashtable(receiver_hashtable_num_of_entries, bucket_size);

    // read input files and insert data in structs
    read_bitcoin_balances_file(bitcoin_balances_file, bitcoin_value,
                               &wallets_ht, &bitcoins_ht, &sender_ht,
                               &receiver_ht);
    int new_transaction_id = read_transaction_file(transaction_file, &sender_ht,
                                                   &receiver_ht, &wallets_ht);

    // ask for user input until user enters "exit"
    char prompt[BUF_SIZE];
    do {
        // empty prompt array before asking for new user input
        memset(prompt, 0, BUF_SIZE);
        printf(YELLOW "Please enter a command: " RESET);
        fgets(prompt, BUF_SIZE, stdin);
        // remove newline character from prompt string
        prompt[strcspn(prompt, "\r\n")] = 0;
        // call function to execute prompts given on the graph
        execute_prompt(prompt, &wallets_ht, &bitcoins_ht);
    } while (strcmp(prompt, "/exit") != 0);

    // Free allocated memory
    free(bitcoin_balances_file);
    free(transaction_file);
    delete_hashtable(&wallets_ht, delete_wallet);
    delete_hashtable(&bitcoins_ht, delete_bitcoin);

    return 0;
}