#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

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
void move(MAZE *maze, struct pos *pos, int direction);
int play(MAZE *maze);
void print_cell(MAZE *maze, int l, int c);
int is_begin(MAZE *maze, int l, int c);
int is_end(MAZE *maze, int l, int c);
int solve(MAZE *maze);
struct termios prepareTerminal();
void getTerminalBack(struct termios *backup);

#endif
