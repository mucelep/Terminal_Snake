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

	printf("\n");
	// Başlık neon yeşil + snake emoji
	printf("\033[1;92m        🐍 WELCOME TO SUPERSNAKE!! 🐍\033[0m\n\n");
	// Zorluk seçimi neon tonlarla
	printf("   \033[1;32m[1]\033[0m  ~~~ EASY MODE ~~~   (Pass through walls)\n\n");
	printf("   \033[1;31m[2]\033[0m  ~~~ HARD MODE ~~~   (Die on walls)\n\n");
	// Gameplay
	printf("\033[1;36m  ╔═══════════════════════════════════════════╗\033[0m\n");
	printf("\033[1;36m  ║  \033[38;2;255;255;0m[W]\033[0m Up    \033[38;2;255;255;0m[A]\033[0m Left  \033[38;2;255;255;0m[S]\033[0m Down  \033[38;2;255;255;0m[D]\033[0m Right  \033[1;36m║\033[0m\n");
	printf("\033[1;36m  ║  \033[1;31m    [Q]\033[0m Quit              \033[1;34m[P]\033[0m Pause      \033[1;36m║\033[0m\n");
	printf("\033[1;36m  ╚═══════════════════════════════════════════╝\033[0m\n");

	read(0,&choise, 1);
	if (choise == '1')
		easy_mode(snake, length, food_x, food_y, &original, obstacles, d);
	else if(choise == '2')
		hard_mode(snake, length, food_x, food_y, &original, obstacles, d);
	else
		printf("WRONG CHOİSE !!");
	return (0);
}
