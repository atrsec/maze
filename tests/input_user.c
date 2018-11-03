#include <stdio.h>
#include <termios.h>

int main()
{

struct termios backup;
tcgetattr(0, &backup);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
struct termios info;
tcgetattr(0, &info);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
info.c_lflag &= ~ICANON;      /* disable canonical mode */
info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
info.c_cc[VTIME] = 0;         /* no timeout */
tcsetattr(0, TCSANOW, &info); /* set immediately */

char c = getchar();
printf("char = %c", c);
c = getchar();
printf("char = %c", c);
c = getchar();
printf("char = %c", c);


tcsetattr(0, TCSANOW, &backup); /* set immediately */

}
