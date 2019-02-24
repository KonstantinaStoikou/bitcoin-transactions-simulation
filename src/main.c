#include <stdio.h>
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
    printf("sender_hashtable_num_of_entries:   %d\n",
           sender_hashtable_num_of_entries);
    printf("receiver_hashtable_num_of_entries: %d\n",
           receiver_hashtable_num_of_entries);
    printf("bucket_size:                       %d\n", bucket_size);

    // read ta arxeia kai eisagogi ton dedomenon tous se domes

    // zitao eisodo apo xristi
    return 0;
}