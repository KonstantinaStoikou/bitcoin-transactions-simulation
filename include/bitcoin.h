#ifndef BITCOIN_HEADER
#define BITCOINS_HEADER

typedef struct Bitcoin {
    char *bitcoin_id;
    // amount of initial value of bitcoin that has remained unspent
    int unspent;
    // number of transaction this bitcoin has participated in
    int num_of_transactions;
    // deiktis se lista me bitcoin ids
} Bitcoin;

#endif