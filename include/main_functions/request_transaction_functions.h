/**
 * Functions to insert data about a transaction in sender/receiver hashtables
 * and bitcoin trees.
 *
 */

#ifndef REQUEST_TRANSACTION_FUNCTIONS_HEADER
#define REQUEST_TRANSACTION_FUNCTIONS_HEADER

#include <time.h>
#include "../data_structs/transaction.h"
#include "../generic_structures/hashtable.h"
#include "../generic_structures/tree.h"

void make_transaction(char *transaction_id, char *sender_wal_id,
                      char *receiver_wal_id, int value, char *date, char *time,
                      Hashtable **wallets, Hashtable **sender_ht,
                      Hashtable **receiver_ht, struct tm **recent_datetime);
// Convert two strings (format: DD-MM-YYYY, HH:MM) to a tm struct and return the
// struct
struct tm *ascii_to_tm(char *date, char *time);
// Traverse bitcoin until all value is traded or there is no more share (DFS
// traversal)
void traverse_bitcoin_tree(Tree_node *node, Transaction **transaction,
                           int *value);
// Compare two struct tm and returns difference transaction_date -
// comparison_date
int compare_datetime(struct tm *transaction_date, struct tm *comparison_date);
// Return a struct tm with current time
struct tm *get_current_time();

#endif