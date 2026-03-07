#include "terminalsnake.h"

void	generate_obstecles(t_segment *obs, int lenght, t_segment *snake)
{
	for (int i = 0; i < OBS_COUNT; i += 3)
	{
		int dir = rand() % 2; // 0 veya 1 yatay mı dikey mi 
		int start_x = rand() % (WIDTH - 4) + 2;
		int start_y = rand() % (HEIGHT - 4) + 2;
		int overlap = 0;

		for (int k = 0; k < lenght; k++)// engeller yılanın içinde oluştu mu kontrolü
		{
			for (int a = 2; a >= 0; a--)
			{
				if(snake[k].x == start_x + a && snake[k].y == start_y)
					overlap = 1;
				if(snake[k].x == start_x && snake[k].y == start_y + a)
					overlap = 1;
			}
		}
		if (!overlap)
		{
			for (int j = 0; j < 3; j++)
			{
				if (dir == 0)
				{
					obs[i + j].x = start_x + j;
					obs[i + j].y = start_y;
				}
				else
				{
					obs[i + j].x = start_x;
					obs[i + j].y = start_y + j;
				}
			}
		}
		if (overlap)
		{
		i -= 3;
		continue;
		}
	}
}