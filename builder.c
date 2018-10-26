#include "builder.h"

labirynthe *build_from_file(char *filename){
	FILE *labFile = fopen(filename, "r");
	if (labFile == NULL)
		fileError("Le fichier n'a pas pu être ouvert.\n");
	return lab;

}

labirynthe *parse_first_line(FILE *f){
	int line, column, bposL, bposC, eposL, eposC;
	int resScan = fscanf(f, "%d %d %d %d %d %d\n", &line, &column, &bposL, &bposC, &eposL, &eposC);
	if (resScan != 6)
		fileError("Error format: line 1\n");
	labirynthe *lab = alloc_labirynthe(line * column);
	lab->line = line;
}

labirynthe *alloc_labirynthe(int nbcells){
	labirynthe *lab = malloc(sizeof(labirynthe));
	lab->cells = malloc(sizeof(short int) * nbcells);
	return lab;
}

void fileError(char *message){
	printf(message);
	exit(1);
}

//labirynthe *build_random(int line, int column);
