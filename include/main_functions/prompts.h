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
                    struct tm *recent_datetime);
// find earnings or payments depending on type argument, type = 1: find
// earnings, type = 2: find payments
void find_transactions(char *wallet_id, Hashtable *ht, char *arg1, char *arg2,
                       char *arg3, char *arg4, int type, int arg_case);
// check what kind of arguments were given and return a number 1-4 depending on
// case 1: no arguments, 2: [time1][year1][time2][year2], 3: [year1][year2], 4:
// [time1][time2]
int check_datetime_arguments(char *arg1, char *arg2, char *arg3, char *arg4);
// check if given datetime is between start and end time, return 1 if between,
// else return 0
int check_time_period(char **start_time, char **end_time, struct tm *datetime);
// check if given datetime is between start and end date, return 1 if between,
// else return 0
int check_date_period(char **start_date, char **end_date, struct tm *datetime);
void print_commands();

#endif