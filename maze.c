#include "maze.h"
#define UP 3
#define RIGHT 2
#define LEFT 0
#define DOWN 1

short int isWall(short int cell, short int wall){
	return (cell >> wall) & 0x0001;
}

short int alreadyDone(short int cell){
	return (cell >> 4) & 0x0001;
}

short int setAlreadyDone(MAZE *maze, struct pos *pos){
	maze->cells[pos->l][pos->c] = maze->cells[pos->l][pos->c] | (0x0010); 
}

void setDisplayBit(MAZE *maze, struct pos *pos, int bool){
	if (bool)
		maze->cells[pos->l][pos->c] = maze->cells[pos->l][pos->c] | 0x0100;
	else
		maze->cells[pos->l][pos->c] = maze->cells[pos->l][pos->c] & 0xFEFF;
}

int isDisplayed(int cell){
	return (cell >> 8) & 0x0001;
}

void printMaze(MAZE *maze){
	for (int i = 0; i < maze->line; i++){
		for(int j = 0; j < maze->column; j++)
			(isWall(maze->cells[i][j], UP)) ?  printf("+-") : printf("+ ");
		printf("+\n");
		for (int j = 0; j < maze->column; j++){
			(isWall(maze->cells[i][j], LEFT))?  printf("|") : printf(" ");
			(isDisplayed(maze->cells[i][j]))? printf("o") : printf(" ");
			if (j + 1 >= maze->column || !isWall(maze->cells[i][j + 1], LEFT)){
				if (isWall(maze->cells[i][j], RIGHT))
					printf("|");
			}
		}
		printf("\n");
	}
	for (int j = 0; j < maze->column; j++)
		(isWall(maze->cells[maze->line - 1][j], DOWN))?  printf("+-"): printf("Error");
	printf("+\n");
}

void update(MAZE *maze){
	system("clear");
	printMaze(maze);
}

int reverseWall(int i){
	switch(i){
		case LEFT:
			return RIGHT;
			break;
		case DOWN:
			return UP;
			break;
		case RIGHT:
			return LEFT;
			break;
		case UP:
			return DOWN;
			break;
		default:
			return -1;
			break;
	}
}

struct pos *nextCell(struct pos *pos, int i){
	struct pos *nextpos = malloc(sizeof(struct pos));
	switch(i){
		case 0:
			nextpos->c = pos->c - 1;
			nextpos->l = pos->l;
			return nextpos;
			break;
		case 1:
			nextpos->l = pos->l + 1;
			nextpos->c = pos->c;
			return nextpos;
			break;
		case 2:
			nextpos->c = pos->c + 1;
			nextpos->l = pos->l;
			return nextpos;
			break;
		case 3:
			nextpos->l = pos->l - 1;
			nextpos->c = pos->c;
			return nextpos;
			break;
		default:
			return NULL;
			break;
	}
}

int noIssue(short int cell){
	for (int i = 0; i < 4; i++)
		if (!isWall(cell, i) && !alreadyDone(cell))
			return 0;
	return 1;
}


int explore(MAZE *maze, struct pos *pos){
	setDisplayBit(maze, pos, 1);
	setAlreadyDone(maze, pos);
	update(maze);
	sleep(1);
	if (maze->end->l == pos->l && maze->end->c == pos->c){
		free(pos);
		printf("Find a way !!!\n");
		return(0);
	}
	int res;
	for (int i = 0; i < 4; i++){
		struct pos *nextpos = nextCell(pos, i);
		if (!isWall(maze->cells[pos->l][pos->c], i) && !alreadyDone(maze->cells[nextpos->l][nextpos->c])){
			res = explore(maze, nextpos);
			if (res == 0){
				free(pos);
				return 0;
			}
			setDisplayBit(maze, nextpos, 0);
		}
		free(nextpos);
	}
	return 1;
}
