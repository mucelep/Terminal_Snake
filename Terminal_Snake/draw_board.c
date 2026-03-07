#include "terminalsnake.h"

void	draw_board(t_segment *snake, int length,int food_x, int food_y, t_segment *obs, int eat)
{
	int y;
	int x;
	int i;
	printf("\033[?25l");		//imleci gizliyor titremeyi önlüyor
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
					printf("\033[0;32m\xe2\x96\x88\033[0m");
			}
			else if (is_snake)
				printf("\033[2;32m\xe2\x96\x93\033[0m");
			else if (is_obstecles)
				printf("\033[38;2;255;0;150mX\033[0m");// engeller kırmızı 
			else if ((y == food_y && x == food_x))
				printf("\033[1;33m*\033[0m");// yem açık sarı
			else if (y == 1 && x == 1)
				printf("\033[1;36m╔\033[0m");           // sol üst köşe
			else if (y == 1 && x == WIDTH)
				printf("\033[1;36m╗\033[0m");           // sağ üst köşe
			else if (y == HEIGHT && x == 1)
				printf("\033[1;36m╚\033[0m");           // sol alt köşe
			else if (y == HEIGHT && x == WIDTH)
				printf("\033[1;36m╝\033[0m");           // sağ alt köşe
			else if (y == 1 || y == HEIGHT)
				printf("\033[1;36m═\033[0m");           // üst/alt kenar
			else if (x == 1 || x == WIDTH)
				printf("\033[1;36m║\033[0m");           // sol/sağ kenar
			else
				printf(" "); // orta alanları bosluk yapıyor 
		}
		printf("\n");
	}
}
