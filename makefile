# OUT  	= bitcoin demo
OUT  	= bitcoin 
CC		= gcc
FLAGS   = -g -Wall

all: $(OUT)

# the app's executable
bitcoin: src/main.c
	$(CC) $(FLAGS) src/main.c src/read_functions.c src/list.c src/prompts.c \
		src/hashtable.c src/wallet.c src/bitcoin.c src/bitcoin_tree_data.c \
		src/tree.c src/transaction.c src/bitcoin_share.c src/transaction_hashtable_data.c \
		-o bitcoin

# a main function for testing new features or changes
# demo: test/main.c
# 	$(CC) $(FLAGS) src/main.c src/read_functions.c src/list.c src/prompts.c \
# 		src/hashtable.c src/wallet.c src/bitcoin.c src/bitcoin_tree_data.c \
# 		src/tree.c src/transaction.c src/bitcoin_share.c -o demo

clean:
	rm -f $(OUT)