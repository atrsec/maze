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
	MAZE *maze = alloc_maze(line * column);
	maze->line = line;
	maze->column = column;
	maze->begin = bposL * column + bposC;
	maze->end = eposL * column + eposC;
	int newCell;
	for(int i = 0; i < line; i++){
		for(int j = 0; j < column; j++){
			resScan = fscanf(f, "%d", &newCell);
			if (resScan != 1)
				fileError("Error format !");
			maze->cells[i * column + j] = newCell;
			fscanf(f, " ");
		}
		fscanf(f, "\n");
	}
	return maze;
	
}

MAZE *alloc_maze(int nbcells){
	MAZE *maze = malloc(sizeof(MAZE));
	maze->cells = malloc(sizeof(short int) * nbcells);
	return maze;
}

void fileError(char *message){
	printf(message);
	exit(1);
}

void printStructMaze(MAZE *maze){
	printf("line = %d\ncolumn = %d\nbegin = %d\nend = %d\n", maze->line, maze->column, maze->begin, maze->end);
	for (int i = 0; i < maze->line * maze->column; i++)
		printf("Pos: %d == %d\n", i, maze->cells[i]); 
}

//MAZE *build_random(int line, int column);
