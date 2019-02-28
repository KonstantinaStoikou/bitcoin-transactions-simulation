#include "../include/print_functions.h"
#include <stdio.h>

// Function to print an integer
void print_int(void *num) { printf("%d", *(int *)num); }
