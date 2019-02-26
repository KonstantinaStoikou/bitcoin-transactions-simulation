/**
 * Functions to read input files and command line arguments.
 *
 */

#ifndef READ_FUNCTIONS_HEADER
#define READ_FUNCTIONS_HEADER

// Read command line arguments and initialize corresponding variables
void read_arguments(int argc, char const *argv[], char **bitcoin_balances_file,
                    char **transaction_file, int *bitcoin_value,
                    int *sender_hashtable_num_of_entries,
                    int *receiver_hashtable_num_of_entries, int *bucket_size);
// Read bitcoin balances file and store items in structures
void read_bitcoin_balances_file(char *filename);
// Read transactions file and store items in structures
void read_transaction_file(char *filename);

#endif