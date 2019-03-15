#include "../../include/main_functions/prompts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_structs/bitcoin_share.h"
#include "../../include/data_structs/bitcoin_tree_data.h"
#include "../../include/data_structs/transaction_hashtable_data.h"
#include "../../include/data_structs/wallet.h"
#include "../../include/generic_structures/tree.h"
#include "../../include/main_functions/read_functions.h"
#include "../../include/main_functions/request_transaction_functions.h"

void execute_prompt(char *prompt, Hashtable **wallets_ht,
                    Hashtable **bitcoins_ht, Hashtable **sender_ht,
                    Hashtable **receiver_ht, char *next_id,
                    struct tm **recent_datetime) {
    // break prompt into words
    char *words[6];  // maximum number of words for a prompt is 6
    for (int i = 0; i < 6; i++) {
        words[i] = NULL;
    }

    int count = 0;
    char *word = strtok(prompt, " ");  // split prompt by spaces
    while (word) {
        words[count] = word;
        count++;
        word = strtok(NULL, " ");
    }
    printf("\n");

    // Request a transaction
    if (strcmp(words[0], "requestTransaction") == 0) {
        if (words[1] == NULL) {
            printf(RED "Sender wallet id was not given.\n\n" RESET);
            return;
        } else if (words[2] == NULL) {
            printf(RED "Receiver wallet id was not given.\n\n" RESET);
            return;
        } else if (words[3] == NULL) {
            printf(RED "Amount of transaction was not given.\n\n" RESET);
            return;
        }
        // check if date was given correctly
        if ((words[4] != NULL) && (words[5] == NULL)) {
            printf(RED "Incomplete date and time.\n");
            return;
        }

        make_transaction(next_id, words[1], words[2], atoi(words[3]), words[4],
                         words[5], wallets_ht, sender_ht, receiver_ht,
                         recent_datetime);
        int next = atoi(next_id);
        next++;
        memset(next_id, 0, strlen(next_id));
        sprintf(next_id, "%d", next);
    }
    // Request multiple transactions
    else if (strcmp(words[0], "requestTransactions") == 0) {
        // check if transactions are from an input file (if only one extra
        // argument was given)
        if (words[2] == NULL) {
            read_input_file(words[1], sender_ht, receiver_ht, wallets_ht,
                            recent_datetime, next_id);
        } else {
            char new_prompt[BUF_SIZE];
            sprintf(new_prompt, "requestTransaction %s %s %s", words[1],
                    words[2], words[3]);
            if (words[4] != NULL) {
                sprintf(new_prompt, " %s", words[4]);
            }
            if (words[5] != NULL) {
                sprintf(new_prompt, " %s", words[5]);
            }
            new_prompt[strcspn(new_prompt, ";")] = 0;
            execute_prompt(new_prompt, wallets_ht, bitcoins_ht, sender_ht,
                           receiver_ht, next_id, recent_datetime);
            // get next transaction
            do {
                // empty prompt array before asking for new user input
                memset(new_prompt, 0, BUF_SIZE);
                fgets(new_prompt, BUF_SIZE, stdin);
                // remove newline character from prompt string
                new_prompt[strcspn(new_prompt, "\r\n")] = 0;
                // if user input does not end in ';' execute prompt as a
                // command
                if (strchr(new_prompt, ';') == NULL) {
                    // call function to execute prompts given on the graph
                    execute_prompt(new_prompt, wallets_ht, bitcoins_ht,
                                   sender_ht, receiver_ht, next_id,
                                   recent_datetime);
                    return;
                } else {
                    // create a string requestTransaction + given arguments
                    // and execute it as a prompt remove ';' character from
                    // prompt string
                    new_prompt[strcspn(new_prompt, ";")] = 0;
                    char new_prompt1[BUF_SIZE];
                    sprintf(new_prompt1, "requestTransaction %s", new_prompt);
                    execute_prompt(new_prompt1, wallets_ht, bitcoins_ht,
                                   sender_ht, receiver_ht, next_id,
                                   recent_datetime);
                }
            } while (1);
        }
    }
    // Show received earnings of a certain user
    else if (strcmp(words[0], "findEarnings") == 0) {
        if (words[1] == NULL) {
            printf(RED "Wallet id was not given.\n\n" RESET);
            return;
        }
        // if odd number of arguments then return
        if ((words[4] != NULL && words[5] == NULL) ||
            (words[2] != NULL && words[3] == NULL)) {
            printf(RED "Wrong number of given arguments.\n\n" RESET);
            return;
        }
        int arg_case =
            check_datetime_arguments(words[2], words[3], words[4], words[5]);
        find_transactions(words[1], *receiver_ht, words[2], words[3], words[4],
                          words[5], 1, arg_case);
    }
    // Show sent payments of a certain user
    else if (strcmp(words[0], "findPayments") == 0) {
        if (words[1] == NULL) {
            printf(RED "Wallet id was not given.\n\n" RESET);
            return;
        }
        // if odd number of arguments then return
        if ((words[4] != NULL && words[5] == NULL) ||
            (words[2] != NULL && words[3] == NULL)) {
            printf(RED "Wrong number of given arguments.\n\n" RESET);
            return;
        }
        int arg_case =
            check_datetime_arguments(words[2], words[3], words[4], words[5]);
        find_transactions(words[1], *sender_ht, words[2], words[3], words[4],
                          words[5], 0, arg_case);
    }
    // Show balance in a certain wallet
    else if (strcmp(words[0], "walletStatus") == 0) {
        if (words[1] == NULL) {
            printf(RED "Wallet id was not given.\n\n" RESET);
            return;
        }
        char *wal_id = words[1];
        int pos = get_hash(get_wallet_hash, wal_id);
        Wallet *wal = (Wallet *)search_hashtable(wallets_ht, pos, wal_id,
                                                 check_wallet_id);
        if (wal == NULL) {
            printf(RED "There is no wallet with the given id.\n\n" RESET);
            return;
        }
        print_wallet(wal);
        printf("\n");
    }
    // Show info about a certain bitcoin
    else if (strcmp(words[0], "bitCoinStatus") == 0) {
        if (words[1] == NULL) {
            perror(RED "Bitcoin id was not given.\n\n" RESET);
            return;
        }
        int bitc_id = atoi(words[1]);
        int pos = get_hash(get_bitcoin_hash, &bitc_id);
        Bitcoin *bitc = (Bitcoin *)search_hashtable(bitcoins_ht, pos, &bitc_id,
                                                    check_bitcoin_id);
        if (bitc == NULL) {
            printf(RED "There is no bitcoin with the given id.\n\n" RESET);
            return;
        }
        print_bitcoin(bitc);
        printf("\n");
    }
    // Show transaction history of a certain bitcoin
    else if (strcmp(words[0], "traceCoin") == 0) {
        if (words[1] == NULL) {
            printf(RED "Bitcoin id was not given.\n\n" RESET);
            return;
        }
        int bitc_id = atoi(words[1]);
        int pos = get_hash(get_bitcoin_hash, &bitc_id);
        Bitcoin *bitc = (Bitcoin *)search_hashtable(bitcoins_ht, pos, &bitc_id,
                                                    check_bitcoin_id);
        if (bitc == NULL) {
            printf(RED "There is no bitcoin with the given id.\n\n" RESET);
            return;
        }
        print_tree_senders(bitc->tree->root, print_bitcoin_transaction);
    }
    // Exit program
    else if (strcmp(words[0], "exit") == 0) {
        printf("Exit program\n");
    }
    // EXTRA PROMPTS FOR DEBUGGING:
    // List all possible commands
    else if (strcmp(words[0], "listCommands") == 0) {
        print_commands();
    }
    // Print bitcoins hashtable
    else if (strcmp(words[0], "showBitcoins") == 0) {
        print_hashtable(*bitcoins_ht, print_bitcoin);
    }
    // Print wallets hashtable
    else if (strcmp(words[0], "showWallets") == 0) {
        print_hashtable(*wallets_ht, print_wallet);
    }
    // Print sender transactions hashtable
    else if (strcmp(words[0], "showSenders") == 0) {
        print_hashtable(*sender_ht, print_transaction_hashtable_data);
    }
    // Print receiver transactions hashtable
    else if (strcmp(words[0], "showReceivers") == 0) {
        print_hashtable(*receiver_ht, print_transaction_hashtable_data);
    }
    // Print bitcoin shares of a given wallet
    else if (strcmp(words[0], "showBitcoinShares") == 0) {
        if (words[1] == NULL) {
            perror(RED "Wallet id was not given.\n\n" RESET);
            return;
        }
        char *wal_id = words[1];
        int pos = get_hash(get_wallet_hash, wal_id);
        Wallet *wal = (Wallet *)search_hashtable(wallets_ht, pos, wal_id,
                                                 check_wallet_id);
        if (wal == NULL) {
            perror(RED "There is no wallet with the given id.\n\n" RESET);
            return;
        }
        print_list(wal->bitcoins_list, print_bitcoin_share);
    }
    // Print bitcoin tree (only data stored in tree, not pointers) of a
    // given bitcoin id
    else if (strcmp(words[0], "showBitcoinTree") == 0) {
        if (words[1] == NULL) {
            perror(RED "Bitcoin id was not given.\n\n" RESET);
            return;
        }
        int bitc_id = atoi(words[1]);
        int pos = get_hash(get_bitcoin_hash, &bitc_id);
        Bitcoin *bitc = (Bitcoin *)search_hashtable(bitcoins_ht, pos, &bitc_id,
                                                    check_bitcoin_id);
        if (bitc == NULL) {
            perror(RED "There is no bitcoin with the given id.\n\n" RESET);
            return;
        }
        print_tree(bitc->tree->root, print_bitcoin_tree_data);
    } else {
        printf(RED "There is no such command.\n" RESET);
    }
}

void find_transactions(char *wallet_id, Hashtable *ht, char *arg1, char *arg2,
                       char *arg3, char *arg4, int type, int arg_case) {
    int pos = get_transaction_hash(wallet_id, ht->num_of_entries);
    Transaction_hashtable_data *thd =
        (Transaction_hashtable_data *)search_hashtable(
            &ht, pos, wallet_id, check_transaction_wallet);
    if (thd == NULL) {
        printf(RED "There is no wallet with the given id\n" RESET);
    }

    // find sum of all transactions inside given dates (if given)
    int sum = 0;
    List_node *current = thd->transactions->head;
    if (type == 1) {
        printf("Received transactions :\n");
    } else {
        printf("Sent transactions :\n");
    }

    if (arg_case == NOARGS) {
        while (current != NULL) {
            printf("\t");
            print_transaction(current->data);
            printf("\n");
            sum += ((Transaction *)current->data)->value;
            current = current->next;
        }
    } else if (arg_case == TIMEONLY) {
        // break arguments to char* arrays
        char *start_time[2];  // maximum number of members of time is 2 (HH:MM)
        int count = 0;
        char *t1 = strtok(arg1, ":");
        while (t1) {
            start_time[count] = t1;
            count++;
            t1 = strtok(NULL, ":");
        }
        char *end_time[2];  // maximum number of members of time is 2 (HH:MM)
        count = 0;
        char *t2 = strtok(arg2, ":");
        while (t2) {
            end_time[count] = t2;
            count++;
            t2 = strtok(NULL, ":");
        }
        while (current != NULL) {
            struct tm *datetime =
                (struct tm *)((Transaction *)current->data)->date;
            if (check_time_period(start_time, end_time, datetime) == 1) {
                printf("\t");
                print_transaction(current->data);
                printf("\n");
                sum += ((Transaction *)current->data)->value;
            }
            current = current->next;
        }
    } else if (arg_case == YEARONLY) {
        char *start_date[3];  // maximum number of members of date is 3
                              // (DD-MM-YYYY)
        int count = 0;
        char *d1 = strtok(arg1, "-");
        while (d1) {
            start_date[count] = d1;
            count++;
            d1 = strtok(NULL, "-");
        }
        char *
            end_date[3];  // maximum number of members of date is 3 (DD-MM-YYYY)
        count = 0;
        char *d2 = strtok(arg2, "-");
        while (d2) {
            end_date[count] = d2;
            count++;
            d2 = strtok(NULL, "-");
        }
        while (current != NULL) {
            struct tm *datetime =
                (struct tm *)((Transaction *)current->data)->date;
            if (check_date_period(start_date, end_date, datetime) == 1) {
                printf("\t");
                print_transaction(current->data);
                printf("\n");
                sum += ((Transaction *)current->data)->value;
            }
            current = current->next;
        }
    } else if (arg_case == TIMEYEAR) {
        struct tm *start_tm = malloc(sizeof(struct tm));
        char *start_date[3];  // maximum number of members of date is 3
                              // (DD-MM-YYYY)
        int count = 0;
        char *d1 = strtok(arg2, "-");
        while (d1) {
            start_date[count] = d1;
            count++;
            d1 = strtok(NULL, "-");
        }
        char *start_time[2];  // maximum number of members of time is 2 (HH:MM)
        count = 0;
        char *t1 = strtok(arg1, ":");
        while (t1) {
            start_time[count] = t1;
            count++;
            t1 = strtok(NULL, ":");
        }

        start_tm->tm_mday = atoi(start_date[0]);
        start_tm->tm_mon = atoi(start_date[1]) - 1;
        start_tm->tm_year = atoi(start_date[2]) - 1900;
        start_tm->tm_hour = atoi(start_time[0]);
        start_tm->tm_min = atoi(start_time[1]);
        start_tm->tm_sec = 0;

        struct tm *end_tm = malloc(sizeof(struct tm));
        char *end_date[3];  // maximum number of members of date is 3
                            // (DD-MM-YYYY)
        count = 0;
        char *d2 = strtok(arg4, "-");
        while (d2) {
            end_date[count] = d2;
            count++;
            d2 = strtok(NULL, "-");
        }
        char *end_time[2];  // maximum number of members of time is 2 (HH:MM)
        count = 0;
        char *t2 = strtok(arg3, ":");
        while (t2) {
            end_time[count] = t2;
            count++;
            t2 = strtok(NULL, ":");
        }

        end_tm->tm_mday = atoi(end_date[0]);
        end_tm->tm_mon = atoi(end_date[1]) - 1;
        end_tm->tm_year = atoi(end_date[2]) - 1900;
        end_tm->tm_hour = atoi(end_time[0]);
        end_tm->tm_min = atoi(end_time[1]);
        end_tm->tm_sec = 0;

        while (current != NULL) {
            struct tm *datetime =
                (struct tm *)((Transaction *)current->data)->date;
            if (compare_datetime(datetime, start_tm) >= 0 &&
                compare_datetime(datetime, end_tm) <= 0) {
                printf("\t");
                print_transaction(current->data);
                printf("\n");
                sum += ((Transaction *)current->data)->value;
            }
            current = current->next;
        }
        free(start_tm);
        free(end_tm);
    }

    if (type == 1) {
        printf("\nTotal earnings of %s : $%d\n", wallet_id, sum);
    } else {
        printf("\nTotal payments of %s : $%d\n", wallet_id, sum);
    }
}

int check_datetime_arguments(char *arg1, char *arg2, char *arg3, char *arg4) {
    // 4 different cases:
    // no arguments, [time1][time2], [year1][year2],
    // [time1][year1][time2][year2]
    if (arg1 == NULL) {
        // case: no arguments
        return NOARGS;
    } else if (arg4 != NULL && arg2 != NULL) {
        // case: [time1][year1][time2][year2]
        // all arguments in correct order
        return TIMEYEAR;
    } else if (strchr(arg1, '-') != NULL) {
        // case: [year1][year2]
        // because first argument contains a "-" which means it's a year
        return YEARONLY;
    } else if (strchr(arg1, ':') != NULL) {
        // case: [time1][time2]
        return TIMEONLY;
    }
    return 0;
}

int check_time_period(char **start_time, char **end_time, struct tm *datetime) {
    // check if datetime is between start and end hours
    if (datetime->tm_hour < atoi(start_time[0]) ||
        datetime->tm_hour > atoi(end_time[0])) {
        return 0;
    } else if (datetime->tm_hour > atoi(start_time[0]) &&
               datetime->tm_hour < atoi(end_time[0])) {
        return 1;
    }
    // if start hour is the same with datetime hour, check minutes
    else if (datetime->tm_hour == atoi(start_time[0]) &&
             datetime->tm_min < atoi(start_time[1])) {
        return 0;
    }
    // if end hour is the same with datetime hour, check minutes
    else if (datetime->tm_hour == atoi(end_time[0]) &&
             datetime->tm_min > atoi(end_time[1])) {
        return 0;
    } else {
        return 1;
    }
}

int check_date_period(char **start_date, char **end_date, struct tm *datetime) {
    // check if datetime is between start and end year
    if (datetime->tm_year + 1900 < atoi(start_date[2]) ||
        datetime->tm_year + 1900 > atoi(end_date[2])) {
        return 0;
    } else if (datetime->tm_year + 1900 > atoi(start_date[2]) &&
               datetime->tm_year + 1900 < atoi(end_date[2])) {
        return 1;
    }
    // if start year is the same with datetime year, check month
    else if (datetime->tm_year + 1900 == atoi(start_date[2]) &&
             datetime->tm_mon + 1 < atoi(start_date[1])) {
        return 0;
    }
    // if end year is the same with datetime year, check month
    else if (datetime->tm_year + 1900 == atoi(end_date[2]) &&
             datetime->tm_mon + 1 > atoi(end_date[1])) {
        return 0;
    }
    // if both start year and start month are the same with datetime year and
    // month, check day
    else if (datetime->tm_year + 1900 == atoi(start_date[2]) &&
             datetime->tm_mon + 1 == atoi(start_date[1]) &&
             datetime->tm_mday < atoi(start_date[0])) {
        return 0;
    }
    // if both end year and end month are the same with datetime year and
    // month, check day
    else if (datetime->tm_year + 1900 == atoi(end_date[2]) &&
             datetime->tm_mon + 1 == atoi(end_date[1]) &&
             datetime->tm_mday > atoi(end_date[0])) {
        return 0;
    } else {
        return 1;
    }
}

void print_commands() {
    printf(BLUE
           "ASSIGNMENT'S TASK PROMPTS: \n\n" CYAN
           "- Request a transaction (optionally date and time) :\n" RESET
           "\trequestTransaction senderWalletID receiverWalletID amount "
           "[date] "
           "[time]\n\n" CYAN
           "- Request multiple transactions (optionally date and time) "
           ":\n" RESET
           "\trequestTransactions senderWalletID receiverWalletID amount "
           "[date] "
           "time;\n"
           "\tsenderWalletID2 receiverWalletID2 amount2 [date2] [time2];\n"
           "\t...\n"
           "\tsenderWalletIDn receiverWalletIDn amountn [daten] "
           "[timen];\n\n" CYAN
           "- Read transactions from an input file as :\n" RESET
           "\trequestTransactions inputFile\n\n" CYAN
           "- Show received earnings of a certain user (optionally in a "
           "certain "
           "time period) "
           ":\n" RESET
           "​\tfindEarnings walletID "
           "[time1][year1][time2][year2]\n\n" CYAN
           "- Show sent payments of a certain user (optionally in a "
           "certain "
           "time "
           "period) :\n" RESET
           "​\tfindPayments walletID "
           "[time1][year1][time2][year2]\n\n" CYAN
           "- Show balance in a certain wallet :\n" RESET
           "​\twalletStatus walletID\n\n" CYAN
           "- Show info about a certain bitcoin :\n" RESET
           "\tbitCoinStatus bitCoinID\n\n" CYAN
           "- Show transaction history of a certain bitcoin :\n" RESET
           "\ttraceCoin bitCoinID\n\n" BLUE "FOR DEBUGGING PURPOSES: \n\n" CYAN
           "- Show wallets' hashtable :\n" RESET "\tshowWallets\n\n" CYAN
           "- Show senders' transactions hashtable :\n" RESET
           "\tshowSenders\n\n" CYAN
           "- Show receivers' transactions hashtable :\n" RESET
           "\tshowReceivers\n\n" CYAN "- Show bitcoins hashtable :\n" RESET
           "\tshowBitcoins\n\n" CYAN
           "- Show bitcoin shares of a certain wallet :\n" RESET
           "\tshowBitcoinShares walletID\n\n" CYAN
           "- Show transactions tree of a certain bitcoin :\n" RESET
           "\tshowBitcoinTree bitCoinID\n\n" CYAN
           "- List all possible commands :\n" RESET "\tlistCommands\n\n" CYAN
           "- Exit program: \n" RESET "\texit\n\n");
    return;
}
