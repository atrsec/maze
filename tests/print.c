#include <stdio.h>

int main() {
	printf("\033[%d;%dH", 10, 5);
	printf("lol\n");
	printf("\033[%d;%dH", 10, 8);
	printf("bla\n");
}
