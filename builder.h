#ifndef BUILDER_H
#define BUILDER_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maze.h"

MAZE *build_from_file(char *filename);
MAZE *build_random();
void fileError(char *message);
MAZE *parse_file(FILE *f);
MAZE *alloc_maze(int line, int column);
void free_maze(MAZE *maze);
void printStructMaze(MAZE *lab);

#endif
