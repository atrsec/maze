#ifndef BUILDER_H
#define BUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct maze {
	int line;
	int column;
	short int *cells;
	int begin;
	int end;
};

typedef struct maze MAZE;

MAZE *build_from_file(char *filename);
MAZE *build_random(int line, int column);
void fileError(char *message);
MAZE *parse_file(FILE *f);
MAZE *alloc_maze(int nbcells);
char *erase_nl(char *line, ssize_t size);
void printMaze(MAZE *lab);

#endif
