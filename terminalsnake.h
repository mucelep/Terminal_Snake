#ifndef TERMINAL_SNAKE_H
# define TERMINAL_SNAKE_H
# define WIDTH 50
# define HEIGHT 25
# define MAX_LENGTH 100

# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <stdlib.h>

struct direction
{
	int dx;
	int dy;
};
typedef struct s_segment
{
	int x;
	int y;
} t_segment;




#endif // TERMINAL_SNAKE_H