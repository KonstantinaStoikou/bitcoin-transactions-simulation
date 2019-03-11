#include "../../include/main_functions/prompts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_structs/bitcoin_share.h"
#include "../../include/data_structs/bitcoin_tree_data.h"
#include "../../include/data_structs/transaction_hashtable_data.h"
#include "../../include/data_structs/wallet.h"
#include "../../include/defines.h"
#include "../../include/generic_structures/tree.h"
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
            perror(RED "Incomplete date and time");
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
            printf("transactions from an input file were requested.\n");
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
                // if user input does not end in ';' execute prompt as a command
                if (strchr(new_prompt, ';') == NULL) {
                    // call function to execute prompts given on the graph
                    execute_prompt(new_prompt, wallets_ht, bitcoins_ht,
                                   sender_ht, receiver_ht, next_id,
                                   recent_datetime);
                    return;
                } else {
                    // create a string requestTransaction + given arguments and
                    // execute it as a prompt
                    // remove ';' character from prompt string
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
        printf("finding earnings\n");
    }
    // Show sent payments of a certain user
    else if (strcmp(words[0], "findPayments") == 0) {
        printf("finding payments\n");
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
        print_tree_senders(bitc->tree->root, print_bitcoin_transactions);
    }
    // Exit program
    else if (strcmp(words[0], "exit") == 0) {
        printf("Exit program\n");
    }
    // EXTRA PROMPTS FOR DEBUGGING:
    // List all possible commands
    else if (strcmp(words[0], "listCommands") == 0) {
        printf(
            BLUE
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
            "​\tfindEarnings walletID [time1][year1][time2][year2]\n\n" CYAN
            "- Show sent payments of a certain user (optionally in a certain "
            "time "
            "period) :\n" RESET
            "​\tfindPayments walletID [time1][year1][time2][year2]\n\n" CYAN
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
    // Print bitcoin tree (only data stored in tree, not pointers) of a given
    // bitcoin id
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

    // printf("\n");
}