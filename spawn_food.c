#include "terminalsnake.h"

void	spawn_food(int *food_x, int *food_y, t_segment *obs, int length, t_segment *snake)
{
	do // yılanın engel içinde spawn olmasını engelle
	{
		*food_x = rand() % (WIDTH - 2) + 2; //yeni rastgele yem
		*food_y = rand() % (HEIGHT - 2) + 2;
		int overlap = 0;
		for (int i = 0; i < OBS_COUNT; i++)
		{
			if(*food_x == obs[i].x && *food_y == obs[i].y) // engelin içinde dogma kontrolü
				overlap = 1;
		}
		for (int i = 0; i < length; i++)
		{
			if (*food_x == snake[i].x && *food_y == snake[i].y) // yılanın içinde dogma kontrolü
				overlap = 1;
		}
		
		if (!overlap)
			break;
	} while (1);
}