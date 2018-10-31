#include "builder.h"
#include "maze.h"

int main(int argc, char *argv[]){
	MAZE *maze = NULL;
	if (argc == 2){
		maze = build_from_file(argv[1]);
	}else{
		maze = build_random();
	}
	int res = explore(maze, maze->begin);
	if (res == 1)
		printf("Impossible to resolve this maze !\n");
	free_maze(maze);

}
