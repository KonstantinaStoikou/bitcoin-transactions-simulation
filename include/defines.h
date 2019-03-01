/**
 * Some defined macros to use throughout the program
 *
 */

#ifndef DEFINES_HEADER
#define DEFINES_HEADER

// Define color codes
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define RESET "\033[0m"

// Define size of buffer for reading user input, formatting strings etc.
#define BUF_SIZE 300
// Define number of entries of wallets hashtable
#define WALLET_HT_SIZE 20
// Define size of buckets of wallets (in bytes)
#define WALLET_BUCKET_SIZE 100
// Define number of entries of bitcoins hashtable
#define BITCOIN_HT_SIZE 20
// Define size of buckets of bitcoins (in bytes)
#define BITCOIN_BUCKET_SIZE 50
// Define size of wallet id string
#define WALLET_ID_SIZE 50
// Define size of transaction id string
#define TRANSACTION_ID_SIZE 10

#endif