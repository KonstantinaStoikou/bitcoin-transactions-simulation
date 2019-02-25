#include <stdio.h>
#include "../include/list.h"
#include "../include/read_functions.h"

int main(int argc, char const *argv[]) {
    printf("THIS IS A TEST MAIN!\n");

    char *bitcoin_balances_file, *transaction_file;
    int bitcoin_value, sender_hashtable_num_of_entries,
        receiver_hashtable_num_of_entries, bucket_size;
    read_arguments(argc, argv, &bitcoin_balances_file, &transaction_file,
                   &bitcoin_value, &sender_hashtable_num_of_entries,
                   &receiver_hashtable_num_of_entries, &bucket_size);
    // printf("bitcoin_balances_file: %s\n", bitcoin_balances_file);
    // printf("transaction_file: %s\n", transaction_file);
    // printf("bitcoin_value: %d\n", bitcoin_value);
    // printf("sender_hashtable_num_of_entries: %d\n",
    //        sender_hashtable_num_of_entries);
    // printf("receiver_hashtable_num_of_entries: %d\n",
    //        receiver_hashtable_num_of_entries);
    // printf("bucket_size: %d\n", bucket_size);

    char *str1 = "hello";
    char *str2 = "hi";
    char *str3 = "my name is";
    char *str4 = "Konstantina";
    char *str5 = "Stoikou";

    List *list = initialize_list();
    add_node(&list, str1);
    add_node(&list, str2);
    add_node(&list, str3);
    add_node(&list, str4);
    add_node(&list, str5);
    print_list(list);
    printf("\n");
    delete_node(&list, str4);
    print_list(list);
    delete_list(&list);
    return 0;
}