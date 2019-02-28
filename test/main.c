/**
 * A main function to test new features or changes in preexisting code.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/defines.h"
#include "../include/hashtable.h"
#include "../include/list.h"
#include "../include/print_functions.h"
#include "../include/prompts.h"
#include "../include/read_functions.h"

int main(int argc, char const *argv[]) {
    printf("THIS IS A TEST MAIN!\n");

    // TEST READING ARGUMENTS HERE:
    // ------------------------------------------------------------------------
    char *bitcoin_balances_file, *transaction_file;
    int bitcoin_value, sender_hashtable_num_of_entries,
        receiver_hashtable_num_of_entries, bucket_size;
    read_arguments(argc, argv, &bitcoin_balances_file, &transaction_file,
                   &bitcoin_value, &sender_hashtable_num_of_entries,
                   &receiver_hashtable_num_of_entries, &bucket_size);
    // ------------------------------------------------------------------------

    // INSERT STATIC VALUES BY HAND IF NO COMMAND LINE ARGUMENTS WERE GIVEN
    // ------------------------------------------------------------------------
    if (argc == 1) {
        bitcoin_balances_file = malloc(strlen("files/bitcoinBalancesFile" + 1));
        strcpy(bitcoin_balances_file, "files/bitcoinBalancesFile");
        transaction_file = malloc(strlen("transactionsFile" + 1));
        strcpy(transaction_file, "transactionsFile");
        bitcoin_value = 50;
        sender_hashtable_num_of_entries = 10;
        receiver_hashtable_num_of_entries = 15;
        bucket_size = 50;
    }
    // printf("bitcoin_balances_file:             %s\n", bitcoin_balances_file);
    // printf("transaction_file:                  %s\n", transaction_file);
    // printf("bitcoin_value:                     %d\n", bitcoin_value);
    // printf("sender_hashtable_num_of_entries:   %d\n",
    //        sender_hashtable_num_of_entries);
    // printf("receiver_hashtable_num_of_entries: %d\n",
    //        receiver_hashtable_num_of_entries);
    // printf("bucket_size:                       %d\n", bucket_size);
    // ------------------------------------------------------------------------

    // TEST READING FILES HERE:
    // ------------------------------------------------------------------------
    // read_bitcoin_balances_file(bitcoin_balances_file);
    // read_transaction_file(transaction_file);
    // ------------------------------------------------------------------------

    // TEST LIST HERE:
    // ------------------------------------------------------------------------
    // char *str1 = "hello";
    // char *str2 = "hi";
    // char *str3 = "my name is";
    // char *str4 = "Konstantina";
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;

    List *list = initialize_list();
    add_list_node(&list, &num1);
    add_list_node(&list, &num2);
    add_list_node(&list, &num3);
    add_list_node(&list, &num4);
    print_list(list, print_int);
    printf("\n");
    delete_list_node(&list, &num4);
    print_list(list, print_int);
    delete_list(&list, NULL);
    // ------------------------------------------------------------------------

    // TEST HASHTABLE HERE:
    // ------------------------------------------------------------------------
    int n = 200;
    printf("size of n %ld\n", sizeof(&n));
    printf("size of int %ld\n", sizeof(int));
    printf("size of Bucket %ld\n", sizeof(Bucket));
    printf("num of entries in bucket : %ld\n",
           (bucket_size - sizeof(Bucket)) / sizeof(int *));
    Hashtable *hashtable =
        initialize_hashtable(sender_hashtable_num_of_entries, bucket_size);
    int insert1 = 100;
    insert_hashtable_entry(&hashtable, 3, &insert1, sizeof(&insert1));
    int insert2 = 101;
    insert_hashtable_entry(&hashtable, 3, &insert2, sizeof(&insert1));
    int insert3 = 102;
    insert_hashtable_entry(&hashtable, 3, &insert3, sizeof(&insert1));
    int insert4 = 103;
    insert_hashtable_entry(&hashtable, 2, &insert4, sizeof(&insert1));
    int insert5 = 104;
    insert_hashtable_entry(&hashtable, 3, &insert5, sizeof(&insert1));
    print_hashtable(hashtable, print_int);
    delete_hashtable(&hashtable);
    // ------------------------------------------------------------------------

    // TEST TREE HERE:
    // ------------------------------------------------------------------------

    // ------------------------------------------------------------------------

    // TEST COLORS HERE:
    // ------------------------------------------------------------------------
    printf("\n");
    printf("%sred\n", RED);
    printf("%sgreen\n", GREEN);
    printf("%syellow\n", YELLOW);
    printf("%sblue\n", BLUE);
    printf("%smagenta\n", MAGENTA);
    printf("%scyan\n", CYAN);
    printf("%snormal\n", RESET);
    // ------------------------------------------------------------------------

    // TEST PROMPTS HERE:
    // ------------------------------------------------------------------------

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
        execute_prompt(prompt);
    } while (strcmp(prompt, "/exit") != 0);
    // ------------------------------------------------------------------------

    free(bitcoin_balances_file);
    free(transaction_file);

    return 0;
}