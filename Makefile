CC=gcc
CFLAGS=-W -Wall -pedantic
EXEC=maze
FILE=src/builder.c src/maze.c src/main.c

all: $(FILE)
	$(CC) -o $(EXEC) $(FILE)

debug:
	$(CC) -o $(EXEC) $(FILE) -g
	gdb $(EXEC)
	
clean:
	rm -rf *.o $(EXEC)
