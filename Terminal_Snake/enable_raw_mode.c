#include "terminalsnake.h"

void	enable_raw_mode(struct termios *orig)
{
	struct termios raw;
	tcgetattr(0, orig);// orjinal stdin ayarlarını orig struct ına atıyor 
	raw = *orig; // raw da saklıyor 
	raw.c_lflag &= ~(ICANON | ECHO);// rawdaki  echo ve canon modu kapatıyor 
	raw.c_cc[VMIN] = 0; //read komutunun minimum karakter beklentisini 0 yapıyor duraklamasın diye
	raw.c_cc[VTIME] = 0;// timeaout sıfırlıyor kaç saniye karakter bekleyeceği 
	tcsetattr(0, TCSANOW, &raw); // degistirdigi raw ayarlarını uyguluyor 
}

void	disenable_raw_mode(struct termios *orig)
{
	tcsetattr(0, TCSANOW, orig); //orjinal ayarları geri uyguluyor tcsanow anında uygulamasına yarıyor 
}

void	clear_screen()
{
	static int i = 0;
	printf("\033[H"); // imleci terminalin sol üstüne getiriyor 
	if(i == 0) // 1 kereliğe mahsus ekranı temizliyor 
	{
		printf("\033[J");
		i++;
	}
}