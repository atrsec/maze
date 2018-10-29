#include "builder.h"

int main(int argc, char *argv[]){
	MAZE *maze = build_from_file(argv[1]);
	printMaze(maze);
}
