#include "../include/prompts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitcoin.h"
#include "../include/bitcoin_tree_data.h"
#include "../include/defines.h"
#include "../include/tree.h"
#include "../include/wallet.h"

void execute_prompt(char *prompt, Hashtable **wallets_ht,
                    Hashtable **bitcoins_ht) {
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

    // request a transaction
    if (strcmp(words[0], "/requestTransaction") == 0) {
        printf("a transaction was requested\n");
    }
    // request multiple transactions
    else if (strcmp(words[0], "/requestTransactions") == 0) {
        printf("multiple transactions were requested\n");
        // check if transactions are from an input file (if only one extra
        // argument was given)
        if (words[2] == NULL) {
            printf("transactions from an input file were requested\n");
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
        printf("showing wallet status\n");
    }
    // Show info about a certain bitcoin
    else if (strcmp(words[0], "/bitcoinStatus") == 0) {
        printf("showing bitcoin status\n");
    }
    // Show transaction history of a certain bitcoin
    else if (strcmp(words[0], "/traceCoin") == 0) {
        if (words[1] == NULL) {
            printf(RED "Bitcoin if was not given\n\n" RESET);
            return;
        }
        int bitc_id = atoi(words[1]);
        int pos = get_hash(get_bitcoin_hash, &bitc_id);
        Bitcoin *bitc = (Bitcoin *)search_hashtable(bitcoins_ht, pos, &bitc_id,
                                                    check_bitcoin_id);
        if (bitc == NULL) {
            printf(RED "There is no bitcoin with the given id\n\n" RESET);
            return;
        }
        print_tree_senders(bitc->tree->root, print_bitcoin_transactions);
    }
    // exit program
    else if (strcmp(words[0], "/exit") == 0) {
        printf("Exit program\n");
    }
    // EXTRA PROMPTS FOR DEBUGGING:
    // list all possible commands
    else if (strcmp(words[0], "/listCommands") == 0) {
        printf(
            CYAN
            "- Request a transaction :\n" RESET
            "\t/requestTransaction senderWalletID receiverWalletID amount date "
            "time\n\n" CYAN "- Request mupliple transactions :\n" RESET
            "\t/requestTransactions senderWalletID receiverWalletID amount "
            "date "
            "time;\n"
            "\tsenderWalletID2 receiverWalletID2 amount2 date2 time2;\n"
            "\t...\n"
            "\tsenderWalletIDn receiverWalletIDn amountn daten timen;\n\n" CYAN
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
            "\t/traceCoin bitCoinID\n\n" CYAN "- Exit program: \n" RESET
            "\t/exit\n\n");
    } else if (strcmp(words[0], "/showBitcoins") == 0) {
        print_hashtable(*bitcoins_ht, print_bitcoin);
    } else if (strcmp(words[0], "/showWallets") == 0) {
        print_hashtable(*wallets_ht, print_wallet);
    } else {
        printf(RED "There is no such command\n" RESET);
    }

    printf("\n");
}