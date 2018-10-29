#include "builder.h"
#include "maze.h"

int main(int argc, char *argv[]){
	MAZE *maze = build_from_file(argv[1]);
	printMaze(maze);
	//isUpWall(maze->cells[0])? printf("oui\n") : printf("non\n");
	//isUpWall(maze->cells[10])? printf("oui\n") : printf("non\n");
	//isUpWall(maze->cells[20])? printf("oui\n") : printf("non\n");
}
