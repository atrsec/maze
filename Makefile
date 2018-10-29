CC=gcc
CFLAGS=-W -Wall -pedantic
EXEC=maze
FILE=builder.c maze.c main.c

all: $(FILE)
	$(CC) -o $(EXEC) $(FILE)

debug:
	$(CC) -o $(EXEC) $(FILE) -g
	gdb $(EXEC)
	
clean:
	rm -rf *.o $(EXEC)
