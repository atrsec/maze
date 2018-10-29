CC=gcc
CFLAGS=-W -Wall -pedantic
EXEC=maze
FILE=builder.c main.c

all: $(FILE)
	$(CC) -o $(EXEC) $(FILE)

debug:
	$(CC) -o $(EXEC) $(FILE) -g
	gdb $(EXEC) tests/mazefile.txt
	
clean:
	rm -rf *.o $(EXEC)
