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

void execute_prompt(char *prompt, Hashtable **wallets_ht,
                    Hashtable **bitcoins_ht, Hashtable **sender_ht,
                    Hashtable **receiver_ht) {
    // break prompt into words
    char *words[6];  // maximum number of words for a prompt is 6
    int count = 0;
    char *word = strtok(prompt, " ");  // split prompt by spaces
    while (word) {
        words[count] = word;
        count++;
        word = strtok(NULL, " ");
    }
    printf("\n");

    // Request a transaction
    if (strcmp(words[0], "/requestTransaction") == 0) {
        printf("a transaction was requested\n");
    }
    // Request multiple transactions
    else if (strcmp(words[0], "/requestTransactions") == 0) {
        printf("multiple transactions were requested.\n");
        // check if transactions are from an input file (if only one extra
        // argument was given)
        if (words[2] == NULL) {
            printf("transactions from an input file were requested.\n");
        }
    }
    // Show received earnings of a certain user
    else if (strcmp(words[0], "/findEarnings") == 0) {
        printf("finding earnings\n");
    }
    // Show sent payments of a certain user
    else if (strcmp(words[0], "/findPayments") == 0) {
        printf("finding payments\n");
    }
    // Show balance in a certain wallet
    else if (strcmp(words[0], "/walletStatus") == 0) {
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
        print_wallet(wal);
        printf("\n");
    }
    // Show info about a certain bitcoin
    else if (strcmp(words[0], "/bitCoinStatus") == 0) {
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
        print_bitcoin(bitc);
        printf("\n");
    }
    // Show transaction history of a certain bitcoin
    else if (strcmp(words[0], "/traceCoin") == 0) {
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
    else if (strcmp(words[0], "/exit") == 0) {
        printf("Exit program\n");
    }
    // EXTRA PROMPTS FOR DEBUGGING:
    // List all possible commands
    else if (strcmp(words[0], "/listCommands") == 0) {
        printf(
            BLUE
            "ASSIGNMENT'S TASK PROMPTS: \n\n" CYAN
            "- Request a transaction (optionally date and time) :\n" RESET
            "\t/requestTransaction senderWalletID receiverWalletID amount "
            "[date] "
            "[time]\n\n" CYAN
            "- Request multiple transactions (optionally date and time) "
            ":\n" RESET
            "\t/requestTransactions senderWalletID receiverWalletID amount "
            "[date] "
            "time;\n"
            "\tsenderWalletID2 receiverWalletID2 amount2 [date2] [time2];\n"
            "\t...\n"
            "\tsenderWalletIDn receiverWalletIDn amountn [daten] "
            "[timen];\n\n" CYAN
            "- Read transactions from an input file as :\n" RESET
            "\t/requestTransactions inputFile\n\n" CYAN
            "- Show received earnings of a certain user (optionally in a "
            "certain "
            "time period) "
            ":\n" RESET
            "​\t/findEarnings walletID [time1][year1][time2][year2]\n\n" CYAN
            "- Show sent payments of a certain user (optionally in a certain "
            "time "
            "period) :\n" RESET
            "​\t/findPayments walletID [time1][year1][time2][year2]\n\n" CYAN
            "- Show balance in a certain wallet :\n" RESET
            "​\t/walletStatus walletID\n\n" CYAN
            "- Show info about a certain bitcoin :\n" RESET
            "\t/bitCoinStatus bitCoinID\n\n" CYAN
            "- Show transaction history of a certain bitcoin :\n" RESET
            "\t/traceCoin bitCoinID\n\n" BLUE
            "FOR DEBUGGING PURPOSES: \n\n" CYAN
            "- Show wallets' hashtable :\n" RESET "\t/showWallets\n\n" CYAN
            "- Show senders' transactions hashtable :\n" RESET
            "\t/showSenders\n\n" CYAN
            "- Show receivers' transactions hashtable :\n" RESET
            "\t/showReceivers\n\n" CYAN "- Show bitcoins hashtable :\n" RESET
            "\t/showBitcoins\n\n" CYAN
            "- Show bitcoin shares of a certain wallet :\n" RESET
            "\t/showBitcoinShares walletID\n\n" CYAN
            "- Show transactions tree of a certain bitcoin :\n" RESET
            "\t/showBitcoinTree bitCoinID\n\n" CYAN
            "- List all possible commands :\n" RESET "\t/listCommands\n\n" CYAN
            "- Exit program: \n" RESET "\t/exit\n\n");
    }
    // Print bitcoins hashtable
    else if (strcmp(words[0], "/showBitcoins") == 0) {
        print_hashtable(*bitcoins_ht, print_bitcoin);
    }
    // Print wallets hashtable
    else if (strcmp(words[0], "/showWallets") == 0) {
        print_hashtable(*wallets_ht, print_wallet);
    }
    // Print sender transactions hashtable
    else if (strcmp(words[0], "/showSenders") == 0) {
        print_hashtable(*sender_ht, print_transaction_hashtable_data);
    }
    // Print receiver transactions hashtable
    else if (strcmp(words[0], "/showReceivers") == 0) {
        print_hashtable(*receiver_ht, print_transaction_hashtable_data);
    }
    // Print bitcoin shares of a given wallet
    else if (strcmp(words[0], "/showBitcoinShares") == 0) {
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
    else if (strcmp(words[0], "/showBitcoinTree") == 0) {
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

    printf("\n");
}