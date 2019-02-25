#include <stdio.h>
#include <string.h>
#include "../include/read_functions.h"

int main(int argc, char const *argv[]) {
    char *bitcoin_balances_file, *transaction_file;
    int bitcoin_value, sender_hashtable_num_of_entries,
        receiver_hashtable_num_of_entries, bucket_size;
    read_arguments(argc, argv, &bitcoin_balances_file, &transaction_file,
                   &bitcoin_value, &sender_hashtable_num_of_entries,
                   &receiver_hashtable_num_of_entries, &bucket_size);
    printf("bitcoin_balances_file:             %s\n", bitcoin_balances_file);
    printf("transaction_file:                  %s\n", transaction_file);
    printf("bitcoin_value:                     %d\n", bitcoin_value);
    printf("sender_hashtanewline character linuxble_num_of_entries:   %d\n",
           sender_hashtable_num_of_entries);
    printf("receiver_hashnewline character linuxtable_num_of_entries: %d\n",
           receiver_hashtable_num_of_entries);
    printf("bucket_size:                       %d\n", bucket_size);

    // read ta arxeia kai eisagogi ton dedomenon tous se domes

    // ask for user input until user enters "exit"
    char prompt[200];
    do {
        // empty prompt array before asking for new user input
        memset(prompt, 0, 200);

        printf("Please enter a command: ");
        fgets(prompt, 200, stdin);
        // remove newline character from prompt string
        prompt[strcspn(prompt, "\r\n")] = 0;
        // call function to execute prompts given on the graph
        // execute_prompt(prompt, &graph);
    } while (strcmp(prompt, "/exit") != 0);

    // apeleuterosi mnimis

    return 0;
}