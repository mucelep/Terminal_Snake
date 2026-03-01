#include "terminalsnake.h"

void	pause_game(t_segment *snake, int lenght, int food_x, int food_y, t_segment *obs, int eat)
{
	char c;
	printf("\033[J");
	while (1)
	{
		printf("\033[H");
		draw_board(snake, lenght, food_x, food_y, obs, 0);
		int n = read(0, &c, 1);
		if(c == 'p')
		{
			printf("\033[J");
			break;
		}
		printf("\033[1;34m=== PAUSED ===\033[0m\n");
		usleep(1000000);
	}
	
}
