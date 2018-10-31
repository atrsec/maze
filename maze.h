#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct maze {
	int line;
	int column;
	short int **cells;
	struct pos *begin;
	struct pos *end;
};

typedef struct maze MAZE;

struct pos {
	int l;
	int c;
};

short int isWall(short int cell, short int line);
void printMaze(MAZE *maze);
void printMazeLine(MAZE *maze, short int line);
int explore(MAZE *maze, struct pos *pos);
void printCurrentPos(MAZE *maze, int pos);
void setDisplayBit(MAZE *maze, struct pos *pos, int bool);
int noIssue(short int cell);

#endif
