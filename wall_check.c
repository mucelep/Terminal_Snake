#include "terminalsnake.h"

int	wallcheck_x(int snake_x)
{
	if(snake_x <= 1)
		snake_x = WIDTH -1; // eger yılanın kafası baslangıc stun a geldiye son stun a ayarlıyor
	if(snake_x >= WIDTH)
		snake_x = 2; // son stuna geldiye baslangıca alıyor 
	return (snake_x);
}

int	wallcheck_y(int snake_y)
{
	if(snake_y <= 1) // aynısının satır hali 
		snake_y = HEIGHT -1;
	if(snake_y >= HEIGHT)
		snake_y = 2;
	return (snake_y);
}
