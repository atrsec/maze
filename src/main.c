#include "builder.h"
#include "maze.h"
#include "time.h"

int main(int argc, char *argv[]){
	MAZE *maze = NULL;
	if (argc >= 2){
		if (strcmp(argv[1], "--nobattle"))
			maze = build_from_file(argv[1]);
		else{
			maze = build_random();
			(solve(maze, 2) == 1)? printf("No way out !\n"):printf("Ez !\n");
			free_maze(maze);
			return 0;
		}
		if (argc > 2 && !strcmp(argv[2], "--nobattle")){
			(solve(maze, 2) == 1)? printf("No way out !\n"):printf("Ez !\n");
			free_maze(maze);
			return 0;
		}

	}else{
		maze = build_random();
	}
	time_t start_t, end_t;
   	double time_user, time_computer;
	int difficulty;
	//USER PLAY
	//RULES
	system("clear");
	printf("Welcome to the maze !!!\nTry to finish the maze before the computer.\nTo navigate in the maze use the i (UP), j (LEFT), k (RIGHT), l (DOWN) of your keyboard.\nChoose the difficuty : 1 => 10 (1 is easy, 10 is impossible)\n");
	int scanres = fscanf(stdin, "%d", &difficulty);
	if (scanres != 1 || difficulty > 10 || difficulty < 1){
		printf("Bad choice, you have already lost\n");
		return 1;
	}
	//LAUNCH GAME
	time(&start_t);
	int res_user = play(maze);
   	time(&end_t);
   	time_user = difftime(end_t, start_t);

	//COMPUTER_PLAY
	//INTRODUCTION
	printf("Let me kick your ass now, press ENTER when you're ready to see an adult movie ! (PSG - Barcelone for example)\n");
	getchar();
	time(&start_t);
	int res_computer = solve(maze, difficulty);
   	time(&end_t);
   	time_computer = difftime(end_t, start_t);
	
	//MESSAGE
	if (res_user > res_computer)
		printf("You're really shit, you don't even finish it !\n");
	else if (res_user == res_computer){
		if (res_user == 1)
			printf("This maze is impossible to finish, decrease the complexity next time hate to loose my time !\n");
		else {
			printf("Time user = %lf (%d)\nTime computer %lf (%d)\n", time_user, res_user, time_computer,res_computer);
			if (time_user > time_computer)
				printf("Too easy, you're a shit.\n");
			else if (time_user < time_computer)
				printf("You won ... it's impossible it's like PSG won the Champions League please increase difficulty it's not realistic !\n");
			else
				printf("DRAW !\n");
		}
	}else{
		printf("Impossible ...\n");
	}
	free_maze(maze);

}
