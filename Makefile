CC=gcc
CFLAGS=-W -Wall -pedantic
EXEC=labirynthe
FILE=builder.c main.c

all: $(FILE)
	$(CC) -o $(EXEC) $(FILE)

debug:
	$(CC) -o $(EXEC) $(FILE) -g
	gdb $(EXEC) tests/labfile.txt
	
clean:
	rm -rf *.o $(EXEC)
