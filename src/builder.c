#include "builder.h"

MAZE *build_from_file(char *filename){
	FILE *mazeFile = fopen(filename, "r");
	if (mazeFile == NULL)
		fileError("Le fichier n'a pas pu être ouvert.\n");
	MAZE *maze = parse_file(mazeFile);
	fclose(mazeFile);
	return maze;

}

MAZE *parse_file(FILE *f){
	int line, column, bposL, bposC, eposL, eposC;
	int resScan = fscanf(f, "%d %d %d %d %d %d\n", &line, &column, &bposL, &bposC, &eposL, &eposC);
	if (resScan != 6)
		fileError("Error format: line 1\n");
	MAZE *maze = alloc_maze(line, column);
	maze->line = line;
	maze->column = column;
	maze->begin->l = bposL;
	maze->begin->c = bposC;
	maze->end->l = eposL;
	maze->end->c = eposC;
	int newCell;
	for(int i = 0; i < line; i++){
		for(int j = 0; j < column; j++){
			resScan = fscanf(f, "%d", &newCell);
			if (resScan != 1)
				fileError("Error format !");
			maze->cells[i][j] = newCell;
			fscanf(f, " ");
		}
		fscanf(f, "\n");
	}
	return maze;
	
}

MAZE *alloc_maze(int line, int column){
	MAZE *maze = malloc(sizeof(MAZE));
	maze->cells = malloc(sizeof(short int *) * line);
	for (int i = 0; i < line; i++)
		maze->cells[i] = malloc(sizeof(short int) * column);
	maze->begin = malloc(sizeof(struct pos));
	maze->end = malloc(sizeof(struct pos));
	return maze;
}

void free_maze(MAZE *maze){
	for(int i = 0; i < maze->line; i++)
		free(maze->cells[i]);
	free(maze->cells);
	free(maze->begin);
	free(maze->end);
	free(maze);
}

void fileError(char *message){
	printf(message);
	exit(1);
}

void printStructMaze(MAZE *maze){
	for (int i = 0; i < maze->line; i++){
		for (int j = 0; j < maze->line; j++)
			printf("%d ", maze->cells[i][j]); 
		printf("\n");
	}
}

void break_wall(MAZE *maze, int l, int c, int chance){
	if (c != maze->column - 1){
		if ((rand() % 100) < chance){
			maze->cells[l][c] = maze->cells[l][c] & 0x000b;
			maze->cells[l][c + 1] = maze->cells[l][c + 1] & 0x000E;
		}
	}
	if (l != maze->line - 1){
		if ((rand() % 100) < chance){
			maze->cells[l][c] = maze->cells[l][c] & 0x000d;
			maze->cells[l + 1][c] = maze->cells[l + 1][c] & 0x0007;
		}
	}
}

MAZE *build_random(){
	srand(time(0));
	int line = 0;
	int column = 0;
	int chance = 0;
	int resscan;
	printf("Maze's number of line:\n");
	resscan = fscanf(stdin,"%d", &line);
	if (resscan != 1)
		fileError("Bad input !\n");
	printf("Maze's number of columns:\n");
	resscan = fscanf(stdin,"%d", &column);
	if (resscan != 1)
		fileError("Bad input !\n");
	MAZE *maze = alloc_maze(line, column);
	maze->line = line;
	maze->column = column;
	printf("Maze's begin (x y):\n");
	resscan = fscanf(stdin,"%d %d", &(maze->begin->l), &(maze->begin->c));
	if (resscan != 2)
		fileError("Bad input !\n");
	printf("Maze's end (x y):\n");
	resscan = fscanf(stdin,"%d %d", &(maze->end->l), &(maze->end->c));
	if (resscan != 2)
		fileError("Bad input !\n");
	if (maze->begin->l >= maze->line || maze->begin->c >= maze->column ||
	    maze->end->l >= maze->line || maze->end->c >= maze->column){
		printf("Error the position is not in the maze !\n");
		exit(1);
	}
	printf("Maze's %% of chance to break the wall:\n");
	resscan = fscanf(stdin,"%d", &chance);
	if (resscan != 1)
		fileError("Bad input !\n");
	for (int i = 0; i < maze->line; i++){
		for (int j = 0; j < maze->column; j++){
			maze->cells[i][j] = 15;
		}
	}
	for (int i = 0; i < maze->line; i++){
		for (int j = 0; j < maze->column; j++){
			break_wall(maze, i, j, chance);
		}
	}
	return maze;
	
}
