/**
 * Functions to read input files and command line arguments.
 *
 */

#ifndef READ_FUNCTIONS_HEADER
#define READ_FUNCTIONS_HEADER

#include <time.h>
#include "../include/hashtable.h"

// Read command line arguments and initialize corresponding variables
void read_arguments(int argc, char const *argv[], char **bitcoin_balances_file,
                    char **transaction_file, int *bitcoin_value,
                    int *sender_hashtable_num_of_entries,
                    int *receiver_hashtable_num_of_entries, int *bucket_size);
// Read bitcoin balances file and store items in structures
void read_bitcoin_balances_file(char *filename, int bitcoin_value,
                                Hashtable **wallets, Hashtable **bitcoins,
                                Hashtable **sender_ht, Hashtable **receiver_ht);
// Read transactions file and store items in structures, return an integer that
// shows the biggest transaction id that will be incremented by 1 for each new
// transaction (after reading the file)
int read_transaction_file(char *filename, Hashtable **sender_ht,
                          Hashtable **receiver_ht, Hashtable **wallets);
// Convert two strings (format: DD-MM-YYYY, HH:MM) to a tm struct and return the
// struct
struct tm *ascii_to_tm(char *date, char *time);

#endif