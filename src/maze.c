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

void print_cell(MAZE *maze, int l, int c){
	if (isDisplayed(maze->cells[l][c])){
		printf ("\033[34;01m%s\033[00m", "😎");
	}
	else{
		if (is_begin(maze, l, c))
			printf ("\033[31;01m%s\033[00m", "⛔");
		else if (is_end(maze, l, c))
			printf ("\033[32;01m%s\033[00m", "✅");
		else
			printf ("\033[31;01m%s\033[00m", "..");
	}
}

void printMaze(MAZE *maze){
	for (int i = 0; i < maze->line; i++){
		for(int j = 0; j < maze->column; j++)
			(isWall(maze->cells[i][j], UP)) ?  (i == 0) ? printf("╦══"): printf("╬══") : (i == 0) ? printf("╦ ") : printf("╬  ");
		(i == 0) ? printf("╦\n") : printf("╬\n");
		for (int j = 0; j < maze->column; j++){
			(isWall(maze->cells[i][j], LEFT))?  printf("║") : printf(" ");
			print_cell(maze, i, j);
			if (j + 1 >= maze->column || !isWall(maze->cells[i][j + 1], LEFT)){
				if (isWall(maze->cells[i][j], RIGHT))
					printf("║");
			}
		}
		printf("\n");
	}
	for (int j = 0; j < maze->column; j++)
		(isWall(maze->cells[maze->line - 1][j], DOWN))?  printf("╬══"): printf("Error");
	printf("╬\n");
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

struct pos nextCell(struct pos *pos, int i){
	struct pos nextpos;
	switch(i){
		case 0:
			nextpos.c = pos->c - 1;
			nextpos.l = pos->l;
			return nextpos;
			break;
		case 1:
			nextpos.l = pos->l + 1;
			nextpos.c = pos->c;
			return nextpos;
			break;
		case 2:
			nextpos.c = pos->c + 1;
			nextpos.l = pos->l;
			return nextpos;
			break;
		case 3:
			nextpos.l = pos->l - 1;
			nextpos.c = pos->c;
			return nextpos;
			break;
	}
}

int noIssue(short int cell){
	for (int i = 0; i < 4; i++)
		if (!isWall(cell, i) && !alreadyDone(cell))
			return 0;
	return 1;
}

int G_DIFFICULTY = 2;

int solve(MAZE *maze, int difficulty){
	G_DIFFICULTY = difficulty;
	struct pos *current_pos = malloc(sizeof(struct pos));
	current_pos->l = maze->begin->l;
	current_pos->c = maze->begin->c;
	int res = explore(maze, current_pos);
	free(current_pos);
	return res;
}


int explore(MAZE *maze, struct pos *pos){
	setDisplayBit(maze, pos, 1);
	setAlreadyDone(maze, pos);
	update(maze);
	usleep(1000000 / G_DIFFICULTY);
	if (maze->end->l == pos->l && maze->end->c == pos->c)
		return(0);
	int res;
	for (int i = 0; i < 4; i++){
		struct pos nextpos = nextCell(pos, i);
		if (!isWall(maze->cells[pos->l][pos->c], i) && !alreadyDone(maze->cells[nextpos.l][nextpos.c])){
			res = explore(maze, &nextpos);
			if (res == 0)
				return 0;
			setDisplayBit(maze, &nextpos, 0);
		}
	}
	return 1;
}

void move(MAZE *maze, struct pos *pos, int direction){
	if (!isWall(maze->cells[pos->l][pos->c], direction)){
		if (direction == DOWN){
			setDisplayBit(maze, pos, 0);
			pos->l = pos->l + 1;
			return;
		}
		else if (direction == UP){
			setDisplayBit(maze, pos, 0);
			pos->l = pos->l - 1;
			return;
		}
		else if (direction == LEFT){
			setDisplayBit(maze, pos, 0);
			pos->c = pos->c - 1;
			return;
		}
		else if (direction == RIGHT){
			setDisplayBit(maze, pos, 0);
			pos->c = pos->c + 1;
			return;
		}else{
			printf("\nBad entry for function move\n");
			return;
		}
	}
}

struct termios prepareTerminal(){
	struct termios backup;
	tcgetattr(0, &backup);
	struct termios info;
	tcgetattr(0, &info);
	info.c_lflag &= ~ICANON;
	info.c_cc[VMIN] = 1;
	info.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &info);
	return backup;
}

void getTerminalBack(struct termios *backup){
	tcsetattr(0, TCSANOW, backup);
}

int play(MAZE *maze){
	struct termios backup = prepareTerminal();
	char c = 's';
	struct pos current = *(maze->begin);
	setDisplayBit(maze, &current, 1);
	update(maze);
	while (c != 'q' && !is_end(maze, current.l, current.c)){
		c = getchar();
		switch (c){
			case 'i':
				move(maze, &current, UP);
				break;
			case 'j':
				move(maze, &current, LEFT);
				break;
			case 'k':
				move(maze, &current, DOWN);
				break;
			case 'l':
				move(maze, &current, RIGHT);
				break;
			defaut:
				break;
		}
		setDisplayBit(maze, &current, 1);
		update(maze);
	}
	if (c != 'q'){
		setDisplayBit(maze, &current, 0);
		getTerminalBack(&backup);
		printf("Congratulation, you find a way !\n");
		return 0;
	}
	setDisplayBit(maze, &current, 0);
	getTerminalBack(&backup);
	printf("Coward !!\n");
	return 1;
}

int is_end(MAZE *maze, int l, int c){
	return 	maze->end->l == l && maze->end->c == c;
}

int is_begin(MAZE *maze, int l, int c){
	return 	maze->begin->l == l && maze->begin->c == c;
}
