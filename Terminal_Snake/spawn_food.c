#include "terminalsnake.h"

void	spawn_food(int *food_x, int *food_y, t_segment *obs, int length, t_segment *snake)
{
	int overlap;
	do // yılanın engel içinde spawn olmasını engelle
	{
		overlap = 0; // üst üste binme yok demek 
		*food_x = rand() % (WIDTH - 2) + 2; //yeni rastgele yem
		*food_y = rand() % (HEIGHT - 2) + 2;
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
		if (*food_x <= 1 || *food_x >= WIDTH || *food_y <= 1 || *food_y >= HEIGHT) // duvar içinde dogma kontrolü
			overlap = 1;
	} while (overlap);
}