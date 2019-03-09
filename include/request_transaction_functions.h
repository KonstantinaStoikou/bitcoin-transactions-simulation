/**
 * Functions to insert transaction data in all corresponding data structures.
 *
 */

#ifndef REQUEST_TRANSACTION_FUNCTIONS_HEADER
#define REQUEST_TRANSACTION_FUNCTIONS_HEADER

#include <time.h>
#include "../include/hashtable.h"

void make_transaction(char *transaction_id, char *sender_wal_id,
                      char *receiver_wal_id, int value, char *date, char *time,
                      Hashtable **wallets, Hashtable **sender_ht,
                      Hashtable **receiver_ht);
// Convert two strings (format: DD-MM-YYYY, HH:MM) to a tm struct and return the
// struct
struct tm *ascii_to_tm(char *date, char *time);

#endif