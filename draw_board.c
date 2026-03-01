#include "terminalsnake.h"

void	draw_board(t_segment *snake, int length,int food_x, int food_y, t_segment *obs, int eat)
{
	int y;
	int x;
	int i;
	for (y = 1; y <= HEIGHT; y++) // oyun alanının uzunlugu her bir satır 
	{
		for ( x = 1; x <= WIDTH; x++) // her bir stun boyunca 
		{
			int is_snake = 0;
			for (i = 0; i < length; i++)
			{
				if(snake[i].x == x && snake[i].y == y)
				is_snake = 1;
			}
			int is_obstecles = 0;
			for (int k = 0; k < OBS_COUNT; k++)
			{
				if (obs[k].x == x && obs[k].y == y)
					is_obstecles = 1;
			}
			if(snake[0].x == x && snake[0].y == y)//yılanın kellesi 
			{
				if (eat)
					printf("\033[31m+\033[0m");// yemek yediyse + olsun
				else
					printf("\033[1;32mO\033[0m");
			}
			else if (is_snake)
				printf("\033[0;32mo\033[0m");
			else if (is_obstecles)
				printf("\033[1;35mX\033[0m");// engeller kırmızı 
			else if ((y == food_y && x == food_x))
				printf("\033[1;33m*\033[0m");// yem açık sarı
			else if(y == 1 || y == HEIGHT )
				printf("#");
			else if ( x == 1 || x == WIDTH)
				printf("#");
			else
				printf(" "); // orta alanları bosluk yapıyor 
		}
		printf("\n");
	}
}
