#include "terminalsnake.h"

int main()
{
	t_segment snake[MAX_LENGTH];
	t_segment obstacles[OBS_COUNT];
	snake_start(snake);
	int length = 3;
	char choise;
	struct termios original; 					// terminalin orjinal degiskenlerini tutmak icin
	struct direction d = {1, 0};				// başlangıç sağa dogru hareket
	srand(time(NULL)); 							// rastgeleliği başlat, her seferinde farklı olsun
	int food_x = rand() % (WIDTH - 2) + 2;			// 2 ile WIDTH-1 arası ---width - 2 aralıgımız sonra + 2 ile 2 o aralıgı kaydırıyoruz
	int food_y = rand() % (HEIGHT - 2) + 2;			// 2 ile HEIGHT-1 arası ---islem önceliginden parantez sonra mod alıyor sonra 2 ekliyor 

	printf("                   Welcome to SUPERSNAKE!! \n\n      Please select defuculty\n\n for EASY mode press '1'     for HARD mode press '2'\n\n");

	read(0,&choise, 1);
	if (choise == '1')
	{
		easy_mode(snake, length, food_x, food_y, &original, obstacles, d);
	}
	else if(choise == '2')
	{
		hard_mode(snake, length, food_x, food_y, &original, obstacles, d);
	}
	else
		printf("WRONG CHOİSE !!");
	return (0);
}
