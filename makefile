OUT  	= bitcoin
CC		= gcc
FLAGS   = -g -Wall

bitcoin: src/main.c
	$(CC) $(FLAGS) src/main.c src/read_functions.c -o bitcoin

clean:
	rm -f $(OUT)