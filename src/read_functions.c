#include "../include/read_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/defines.h"

void read_arguments(int argc, char const *argv[], char **bitcoin_balances_file,
                    char **transaction_file, int *bitcoin_value,
                    int *sender_hashtable_num_of_entries,
                    int *receiver_hashtable_num_of_entries, int *bucket_size) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            *bitcoin_balances_file = malloc(strlen(argv[i + 1]) + 1);
            strcpy(*bitcoin_balances_file, argv[i + 1]);
        } else if (strcmp(argv[i], "-t") == 0) {
            *transaction_file = malloc(strlen(argv[i + 1]) + 1);
            strcpy(*transaction_file, argv[i + 1]);
        } else if (strcmp(argv[i], "-v") == 0) {
            *bitcoin_value = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-h1") == 0) {
            *sender_hashtable_num_of_entries = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-h2") == 0) {
            *receiver_hashtable_num_of_entries = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-b") == 0) {
            *bucket_size = atoi(argv[i + 1]);
        }
    }
}

void read_bitcoin_balances_file(char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    // format path because of folder structure
    char filepath[BUF_SIZE];
    snprintf(filepath, sizeof filepath, "%s%s", "./", filename);

    fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror("Balances file cannot be opened");
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, fp) != -1) {
        printf("%s", line);
        char *word = strtok(line, " ");
        printf("username is : %s\n", word);
        while (word) {
            word = strtok(NULL, " ");
            printf("bitcoin is : %s\n", word);
        }
    }
    printf("\n");
    fclose(fp);
}
