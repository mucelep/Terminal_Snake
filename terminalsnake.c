#include "terminalsnake.h"

void draw_board(t_segment *snake, int length,int food_x, int food_y, t_segment *obs, int eat)
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
	struct direction dir = {0, 0};
	if(c == 'd')
	{
		dir.dx = 1; // sağa doğru 1 hareket
		dir.dy = 0;
	}
	else if(c == 'a')
	{
		dir.dx = -1; //sola doğru 1 hareket
		dir.dy = 0;
	}
	else if(c == 's')
	{
		dir.dx = 0;
		dir.dy = 1; // assagı dogru 1 hareket
	}
	else if(c == 'w')
	{
		dir.dx = 0; // yukarı dogru 1 hareket
		dir.dy = -1;
	}
	return (dir);
}

void save_score(int score)
{
	int best = 0;
	char buf[20];
	int n;
	int fd = open("score.txt", O_CREAT | O_RDONLY, 0777);
	if (fd != -1)
	{
		n = read(fd , buf, sizeof(buf));
		buf[n] = '\0';
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

void generate_obstecles(t_segment *obs, int lenght, t_segment *snake)
{
	for (int i = 0; i < OBS_COUNT; i += 3)
	{
		int dir = rand() % 2; // 0 veya 1 yatay mı dikey mi 
		int start_x = rand() % (WIDTH - 4) + 2;
		int start_y = rand() % (HEIGHT - 4) + 2;
		int overlap = 0;

		for (int k = 0; k < lenght; k++)// engeller yılanın içinde oluştu mu kontrolü
		{
			for (int a = 2; a >= 0; a--)
			{
				if(snake[k].x == start_x + a && snake[k].y == start_y)
					overlap = 1;
				if(snake[k].x == start_x && snake[k].y == start_y + a)
					overlap = 1;
			}
		}
		if (!overlap)
		{
			for (int j = 0; j < 3; j++)
			{
				if (dir == 0)
				{
					obs[i + j].x = start_x + j;
					obs[i + j].y = start_y;
				}
				else
				{
					obs[i + j].x = start_x;
					obs[i + j].y = start_y + j;
				}
			}
		}
	}
}

void spawn_food(int *food_x, int *food_y, t_segment *obs, int length, t_segment *snake)
{
	do // yılanın engel içinde spawn olmasını engelle
	{
		*food_x = rand() % (WIDTH - 2) + 2; //yeni rastgele yem
		*food_y = rand() % (HEIGHT - 2) + 2;
		int overlap = 0;
		for (int i = 0; i < OBS_COUNT; i++)
		{
			if(*food_x == obs[i].x && *food_y == obs[i].y) // engelin içinde dogma kontrolü
				overlap = 1;
		}
		for (int i = 0; i < length; i++)
		{
			if (*food_x == snake[i].x && *food_y == snake[i].y) // yılanın içinde dogma kontrolü
				overlap = 1;
		}
		
		if (!overlap)
			break;
	} while (1);
}

void game_over_animation(t_segment *snake, int length, int food_x, int food_y, t_segment *obs, int score)
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
void pause_game(char c)
{
	
}
int main()
{
	t_segment snake[MAX_LENGTH];
	t_segment obstacles[OBS_COUNT];
	snake[0].x = 5;// yılanın başlangıç kordinatları
	snake[0].y = 5;
	snake[1].x = 4;
	snake[1].y = 5;
	snake[2].x = 3;
	snake[2].y = 5;
	int length = 3;
	char c;
	char choise;
	struct termios original; // terminalin orjinal degiskenlerini tutmak icin
	struct direction d = {1, 0};// başlangıç sağa dogru hareket
	srand(time(NULL));  // rastgeleliği başlat, her seferinde farklı olsun
	int food_x = rand() % (WIDTH - 2) + 2;   // 2 ile WIDTH-1 arası ---width - 2 aralıgımız sonra + 2 ile 2 o aralıgı kaydırıyoruz
	int food_y = rand() % (HEIGHT - 2) + 2;  // 2 ile HEIGHT-1 arası ---islem önceliginden parantez sonra mod alıyor sonra 2 ekliyor 
	printf("                   Welcome to SUPERSNAKE!! \n\n      Please select defuculty\n\n for EASY mode press '1'     for HARD mode press '2'\n\n");
	read(0,&choise, 1);
	if (choise == '1')
	{
		enable_raw_mode(&original);
		while (read(0, &c, 1) > 0);
		while (1)
		{
			clear_screen();
			draw_board(snake,length,food_x,food_y, obstacles, 0); // oyun alanını çiziyor 
			printf("score = %d\n", length - 3);
			int n = read(0, &c, 1);
			if (n > 0)
			{
				if(c == 'q')
					break;
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
				disenable_raw_mode(&original);
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
				usleep(200000);
			else
				usleep(130000);
		}
		disenable_raw_mode(&original);
	}
	else if(choise == '2')
	{
		int speed = 100000;
		enable_raw_mode(&original);
		while (read(0, &c, 1) > 0);
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
				disenable_raw_mode(&original);
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
				disenable_raw_mode(&original);
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
				disenable_raw_mode(&original);
				game_over_animation(snake, length, food_x, food_y, obstacles, length - 3);
				return (0);
			}
			if(d.dy != 0)
				usleep(speed * 1.7);
			else
				usleep(speed);
		}	
		disenable_raw_mode(&original);
	}
	else
		printf("WRONG CHOİSE !!");
	return (0);
}
