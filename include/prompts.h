/**
 * Functions to execute prompts given by the user.
 *
 */

#ifndef PROMPTS_HEADER
#define PROMPTS_HEADER

#include "../include/hashtable.h"

// Execute a command given by the user
void execute_prompt(char *prompt, Hashtable **wallets_ht,
                    Hashtable **bitcoins_ht);

#endif