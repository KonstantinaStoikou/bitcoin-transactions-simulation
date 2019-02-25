#include "../include/prompts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_prompt(char *prompt) {
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
    else if (strcmp(words[0], "/requestTransaction") == 0) {
        printf("multiple transactions were requested\n");
        // add_edge(graph, words[1], words[2], atoi(words[3]));
        // printf("- Inserted |%s|->%s->|%s|\n", words[1], words[3], words[2]);
    }
    // exit program
    else if (strcmp(words[0], "/exit") == 0) {
        printf("Exit program\n");
    }
    // EXTRA PROMPTS FOR DEBUGGING:
    else if (strcmp(words[0], "/listCommands") == 0) {
        printf(
            "- Request a transaction :\n"
            "\t/requestTransaction senderWalletID receiverWalletID amount date "
            "time\n\n"
            "- Request mupliple transactions :\n"
            "\t/requestTransactions senderWalletID receiverWalletID amount "
            "date "
            "time;\n"
            "\tsenderWalletID2 receiverWalletID2 amount2 date2 time2;\n"
            "\t...\n"
            "\tsenderWalletIDn receiverWalletIDn amountn daten timen;\n\n"
            "- Read transactions from an input file as :\n"
            "\t/requestTransactions inputFile\n\n"
            "- Show received earnings of a certain user (optionally in a "
            "certain "
            "time period) "
            ":\n"
            "​\t/findEarnings walletID [time1][year1][time2][year2]\n\n"
            "- Show sended payments of a certain user (optionally in a certain "
            "time "
            "period) :\n"
            "​\t/findPayments walletID [time1][year1][time2][year2]\n\n"
            "- Show balance in a certain wallet :\n"
            "​\t/walletStatus walletID\n\n"
            "- Show info about a certain bitcoin :\n"
            "\t/bitCoinStatus bitCoinID\n\n"
            "- Show transaction history of a certain bitcoin :\n"
            "\t/traceCoin bitCoinID\n\n"
            "- Exit program: \n"
            "\t/exit\n\n");
    } else {
        printf("There is no such command\n");
    }

    printf("\n");
}