#include "terminalsnake.h"

int	easy_mode(t_segment *snake, int length, int food_x, int food_y, struct termios *original, t_segment *obstacles, struct direction d)
{
	char c;
	enable_raw_mode(original);
	while (read(0, &c, 1) > 0);
	memset(obstacles, 0, sizeof(*obstacles));
	while (1)
	{
		clear_screen();
		draw_board(snake,length, food_x, food_y, obstacles, 0); // oyun alanını çiziyor 
		printf("score = %d\n", length - 3);
		int n = read(0, &c, 1);
		if (n > 0)
		{
			if (c == 'q')
				break;
			if (c == 'p')
				pause_game(snake, length, food_x, food_y, obstacles);
			struct direction new_d = check_way(c);
			if ((new_d.dx != 0 || new_d.dy != 0) && // wasd den başka bir tuşa bastıysa 
				!(new_d.dx == -d.dx && new_d.dy == -d.dy))// 180 derece dönüş kontrolü 
				d = new_d;
			
		}
		for(int i = length - 1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y; //yılanı hareket ettirme 
		}
		snake[0].x += d.dx;
		snake[0].y += d.dy;
		snake[0].x = wallcheck_x(snake[0].x);
		snake[0].y = wallcheck_y(snake[0].y); // duvara degme kontrolü 
		int	hit = 0;
		for (int i = 1; i < length; i++) // kendine çarpma kontrolü
		{
			if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
				hit = 1;
		}
		if (hit)
		{
			disenable_raw_mode(original);
			game_over_animation(snake, length, food_x, food_y, obstacles, length - 3);
			return (0);
		}
		if (snake[0].x == food_x && snake[0].y == food_y)//yem kontrolü
		{
			length++;
			spawn_food(&food_x, &food_y, obstacles, length, snake);
			printf("\033[H");
			draw_board(snake,length,food_x,food_y,obstacles,1);// yem yeme animasyonu 
			usleep(150000);
			printf("\033[H");
			draw_board(snake,length,food_x,food_y,obstacles,0);
		}
		if(d.dy != 0)
			usleep(170000);
		else
			usleep(100000);
	}
	disenable_raw_mode(original);
	return (0);
}