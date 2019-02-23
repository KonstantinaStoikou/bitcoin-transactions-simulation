OUT  	= bitcoin demo
CC		= gcc
FLAGS   = -g -Wall

all: $(OUT)

# the app executable
bitcoin: src/main.c
	$(CC) $(FLAGS) src/main.c src/read_functions.c -o bitcoin

# a main function for testing new features or changes
demo: test/main.c
	$(CC) $(FLAGS) test/main.c src/read_functions.c -o demo

clean:
	rm -f $(OUT)