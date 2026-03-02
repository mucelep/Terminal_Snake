#include "terminalsnake.h"

int	hard_mode(t_segment *snake, int length, int food_x, int food_y, struct termios *original, t_segment *obstacles, struct direction d)
{
	char c;
	int speed = 100000;
	enable_raw_mode(original);
	while (read(0, &c, 1) > 0);
	generate_obstecles(obstacles, length, snake);
	while (1)
	{
		clear_screen();
		
		draw_board(snake,length,food_x,food_y, obstacles, 0);//oyun alanını çiziyor
		printf("score = %d\n", length - 3);//alta score yazıyor
		int n = read(0, &c, 1);
		if (n > 0) // yönü okusun ve yeni bir tus gelene kadar degisiklik yapmasın 
		{
			if(c == 'q')
				break;
			if (c == 'p')
				pause_game(snake, length, food_x, food_y, obstacles);
			struct direction new_d = check_way(c); //kontrol için geçici struct
			if ((new_d.dx != 0 || new_d.dy != 0) && // wasd den başka bir tuşa bastıysa 
				!(new_d.dx == -d.dx && new_d.dy == -d.dy))// 180 derece dönüş kontrolü eğer ki tam tersi değilse yeni yönü güncelliyor
				d = new_d;
		}
		for(int i = length - 1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x;// yılanı orantılı şekilde hareket ettirme 
			snake[i].y = snake[i - 1].y;
		}
		snake[0].x += d.dx; //kafanın yeni konumu 
		snake[0].y += d.dy;
		if (snake[0].x <= 1 || snake[0].x >= WIDTH ||
			snake[0].y <= 1 || snake[0].y >= HEIGHT )
		{
			disenable_raw_mode(original);
			game_over_animation(snake, length, food_x, food_y, obstacles, length - 3);
			return (0);
		}
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
			if (speed > 40000)// hızı arttırma 
				speed -= 5000;
			generate_obstecles(obstacles, length, snake);// yemek yedikçe yeni yerde üretiyo 
			printf("\033[H");// yem yeme animasyonu 
			draw_board(snake,length,food_x,food_y,obstacles,1);
			usleep(0600000);
			printf("\033[H");
			draw_board(snake,length,food_x,food_y,obstacles,0);
		}
		int	wall = 0;
		for (int w = 0; w < OBS_COUNT; w++) // ENGELLERE ÇARPMA KONTROLÜ
		{
			if (snake[0].x == obstacles[w].x && obstacles[w].y == snake[0].y)
				wall = 1;
		}
		if (wall)
		{
			disenable_raw_mode(original);
			game_over_animation(snake, length, food_x, food_y, obstacles, length - 3);
			return (0);
		}
		if(d.dy != 0)
			usleep(speed * 1.7);
		else
			usleep(speed);
	}	
	disenable_raw_mode(original);
	return (0);
}