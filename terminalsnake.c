#include "terminalsnake.h"

void draw_board(t_segment *snake, int length,int food_x, int food_y)
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
			if(snake[0].x == x && snake[0].y == y)
				printf("O");
			else if(is_snake) 
				printf("o");
			else if (y == food_y && x == food_x)
				printf("*");
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

void clear_screen()
{
	static int i = 0;
	printf("\033[H"); // imleci terminalin sol üstüne getiriyor 
	if(i == 0) // 1 kereliğe mahsus ekranı temizliyor 
	{
		printf("\033[J");
		i++;
	}
}

int wallcheck_x(int snake_x)
{
	if(snake_x <= 1)
		snake_x = WIDTH -1; // eger yılanın kafası baslangıc stun a geldiye son stun a ayarlıyor
	if(snake_x >= WIDTH)
		snake_x = 2; // son stuna geldiye baslangıca alıyor 
	return (snake_x);
}

int wallcheck_y(int snake_y)
{
	if(snake_y <= 1) // aynısının satır hali 
		snake_y = HEIGHT -1;
	if(snake_y >= HEIGHT)
		snake_y = 2;
	return (snake_y);
}

void enable_raw_mode(struct termios *orig)
{
	struct termios raw;
	tcgetattr(0, orig);// orjinal stdin ayarlarını orig struct ına atıyor 
	raw = *orig; // raw da saklıyor 
	raw.c_lflag &= ~(ICANON | ECHO);// rawdaki  echo ve canon modu kapatıyor 
	raw.c_cc[VMIN] = 0; //read komutunun minimum karakter beklentisini 0 yapıyor duraklamasın diye
	raw.c_cc[VTIME] = 0;// timeaout sıfırlıyor kaç saniye karakter bekleyeceği 
	tcsetattr(0, TCSANOW, &raw); // degistirdigi raw ayarlarını uyguluyor 
}

void disenable_raw_mode(struct termios *orig)
{
	tcsetattr(0, TCSANOW, orig); //orjinal ayarları geri uyguluyor tcsanow anında uygulamasına yarıyor 
}
// yönleri kontrol ediyor 
struct direction check_way(char c)
{
	struct direction dir;
	if(c == 'd')
	{
		dir.dx = 1; // sağa doğru 1 hareket
		dir.dy = 0;
	}
		if(c == 'a')
	{
		dir.dx = -1; //sola doğru 1 hareket
		dir.dy = 0;
	}
		if(c == 's')
	{
		dir.dx = 0;
		dir.dy = 1; // assagı dogru 1 hareket
	}
		if(c == 'w')
	{
		dir.dx = 0; // yukarı dogru 1 hareket
		dir.dy = -1;
	}
	return (dir);
}

int main()
{
	t_segment snake[MAX_LENGTH];
	snake[0].x = 5;
	snake[0].y = 5;
	int length = 3;
	char c;
	char choise;
	struct termios original;
	struct direction d = {1, 0};
	srand(time(NULL));  // rastgeleliği başlat, her seferinde farklı olsun
	int food_x = rand() % (WIDTH - 2) + 2;   // 2 ile WIDTH-1 arası
	int food_y = rand() % (HEIGHT - 2) + 2;  // 2 ile HEIGHT-1 arası
	printf("                   Welcome to SUPERSNAKE!! \n\n      Please select defuculty\n\n for EASY mode press '1'     for HARD mode press '2'\n\n");
	read(0,&choise, 1);
	if (choise == '1')
	{
		enable_raw_mode(&original);
		while (read(0, &c, 1) > 0);
		while (1)
		{
			clear_screen();
			draw_board(snake,length,food_x,food_y);
			int n = read(0, &c, 1);
			if (n > 0)
			{
				if(c == 'q')
					break;
				d = check_way(c);
			}
			for(int i = length - 1; i > 0; i--)
			{
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
			snake[0].x += d.dx;
			snake[0].y += d.dy;
			snake[0].x = wallcheck_x(snake[0].x);
			snake[0].y = wallcheck_y(snake[0].y);
			if (snake[0].x == food_x && snake[0].y == food_y)
			{
				length++;
				food_x = rand() % (WIDTH - 2) + 2;
				food_y = rand() % (HEIGHT - 2) + 2;
			}
			if(d.dy != 0)
				usleep(200000);
			else
				usleep(130000);
		}
		disenable_raw_mode(&original);
	}
	else if(choise == '2')
	{
		
	}
	else
		printf("WRONG CHOİSE !!");
	return 0;
}
