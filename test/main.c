/**
 * A main function to test new features or changes in preexisting code.
 *
 */

#include <stdio.h>
#include <string.h>
#include "../include/defines.h"
#include "../include/list.h"
#include "../include/prompts.h"
#include "../include/read_functions.h"

int main(int argc, char const *argv[]) {
    printf("THIS IS A TEST MAIN!\n");

    // TEST READING ARGUMENTS HERE:
    char *bitcoin_balances_file, *transaction_file;
    int bitcoin_value, sender_hashtable_num_of_entries,
        receiver_hashtable_num_of_entries, bucket_size;
    read_arguments(argc, argv, &bitcoin_balances_file, &transaction_file,
                   &bitcoin_value, &sender_hashtable_num_of_entries,
                   &receiver_hashtable_num_of_entries, &bucket_size);
    printf("bitcoin_balances_file: %s\n", bitcoin_balances_file);
    // printf("transaction_file: %s\n", transaction_file);
    // printf("bitcoin_value: %d\n", bitcoin_value);
    // printf("sender_hashtable_num_of_entries: %d\n",
    //        sender_hashtable_num_of_entries);
    // printf("receiver_hashtable_num_of_entries: %d\n",
    //        receiver_hashtable_num_of_entries);
    // printf("bucket_size: %d\n", bucket_size);

    // TEST READING FILES HERE:
    read_bitcoin_balances_file(bitcoin_balances_file);
    read_transaction_file(transaction_file);

    // TEST LIST HERE:
    char *str1 = "hello";
    char *str2 = "hi";
    char *str3 = "my name is";
    char *str4 = "Konstantina";

    List *list = initialize_list();
    add_list_node(&list, str1);
    add_list_node(&list, str2);
    add_list_node(&list, str3);
    add_list_node(&list, str4);
    print_list(list);
    printf("\n");
    delete_list_node(&list, str4);
    print_list(list);
    delete_list(&list);

    // TEST COLORS HERE:
    printf("%sred\n", RED);
    printf("%sgreen\n", GREEN);
    printf("%syellow\n", YELLOW);
    printf("%sblue\n", BLUE);
    printf("%smagenta\n", MAGENTA);
    printf("%scyan\n", CYAN);
    printf("%snormal\n", RESET);

    // TEST PROMPTS HERE:

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

    // TEST TREE HERE:

    return 0;
}