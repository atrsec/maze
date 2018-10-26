#ifndef BUILDER_H
#define BUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct labirynthe {
	int line;
	int column;
	short int *cells;
	int begin;
	int end;
};

typedef struct labirynthe labirynthe;

labirynthe *build_from_file(char *filename);
labirynthe *build_random(int line, int column);
void fileError(char *message);
labirynthe *parse_first_line(char *line);
labirynthe *alloc_labirynthe(int nbcells);
char *erase_nl(char *line, ssize_t size);

#endif
