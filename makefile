OUT  	= bitcoin 
CC		= gcc
FLAGS   = -g -Wall

all: $(OUT)

# the app's executable
bitcoin: src/main.c
	$(CC) $(FLAGS) src/data_structs/*.c src/generic_structures/*.c src/main_functions/*.c \
		src/main.c -o bitcoin

# bitcoin: src/main.c
# 	$(CC) $(FLAGS) src/main.c src/read_functions.c src/list.c src/prompts.c \
# 		src/hashtable.c src/wallet.c src/bitcoin.c src/bitcoin_tree_data.c \
# 		src/tree.c src/transaction.c src/bitcoin_share.c src/transaction_hashtable_data.c \
# 		src/request_transaction_functions.c -o bitcoin

clean:
	rm -f $(OUT)