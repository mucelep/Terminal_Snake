#ifndef TERMINAL_SNAKE_H
# define TERMINAL_SNAKE_H
# define WIDTH 50
# define HEIGHT 25
# define MAX_LENGTH 100
# define OBS_COUNT 9

# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

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

struct	direction check_way(char c);

int		hard_mode(t_segment *snake, int length, int food_x, int food_y, struct termios *original, t_segment *obstacles, struct direction d);
int		easy_mode(t_segment *snake, int length, int food_x, int food_y, struct termios *original, t_segment *obstacles, struct direction d);
int		wallcheck_x(int snake_x);
int		wallcheck_y(int snake_y);

void	game_over_animation(t_segment *snake, int length, int food_x, int food_y, t_segment *obs, int score);
void	draw_board(t_segment *snake, int length,int food_x, int food_y, t_segment *obs, int eat);
void	pause_game(t_segment *snake, int lenght, int food_x, int food_y, t_segment *obs);
void	spawn_food(int *food_x, int *food_y, t_segment *obs, int length, t_segment *snake);
void	generate_obstecles(t_segment *obs, int lenght, t_segment *snake);
void	disenable_raw_mode(struct termios *orig);
void	enable_raw_mode(struct termios *orig);
void	snake_start(t_segment *snake);
void	save_score(int score);
void	clear_screen();

#endif // TERMINAL_SNAKE_H