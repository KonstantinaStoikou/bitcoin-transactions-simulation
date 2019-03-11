/**
 * Functions to execute prompts given by the user.
 *
 */

#ifndef PROMPTS_HEADER
#define PROMPTS_HEADER

#include <time.h>
#include "../generic_structures/hashtable.h"

// Execute a command given by the user
void execute_prompt(char *prompt, Hashtable **wallets_ht,
                    Hashtable **bitcoins_ht, Hashtable **sender_ht,
                    Hashtable **receiver_ht, char *next_id,
                    struct tm **recent_datetime);

#endif