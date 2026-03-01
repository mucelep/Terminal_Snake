#include "terminalsnake.h"

// yönleri kontrol ediyor 
struct direction	check_way(char c)
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
