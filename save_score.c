#include "terminalsnake.h"

void	save_score(int score)
{
	int best = 0;
	char buf[20];
	int n;
	int fd = open("score.txt", O_CREAT | O_RDONLY, 0777);
	if (fd != -1)
	{
		n = read(fd , buf, sizeof(buf));
		if(n > 0)
			buf[n] = '\0';
		else
			buf[0] = '\0';
		best = atoi(buf);
		close(fd);
	}
	if (score > best)
		best = score;
	fd = open("score.txt", O_WRONLY | O_TRUNC , 0777);
	if (fd != -1)
	{
		n = snprintf(buf, sizeof(buf), "%d", best);
		write(fd, buf, n);
		close(fd);
	}
	printf("\033[0;33m┏━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃ SCORE: %-4d| BEST: %-4d┃\n", score, best);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m\n");
}

void	game_over_animation(t_segment *snake, int length, int food_x, int food_y, t_segment *obs, int score)
{
	printf("\033[J");
	for (int i = 0; i < 6; i++)
	{
	printf("\033[H");
	draw_board(snake, length, food_x, food_y, obs, 0);
		if (i % 2 == 0)
			printf("\033[41m   GAME OVER !!!   \033[0m\n");
		else
			printf("                    \n");
		usleep(200000);
	}
	printf("\033[H\033[J");
	save_score(score);
}