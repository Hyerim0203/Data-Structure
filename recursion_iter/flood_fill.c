#include <stdio.h>

#define WHITE 0
#define BLACK 1
#define YELLOW 2
#define WIDTH 10
#define HEIGHT 10

int screen[WIDTH][HEIGHT];

char read_pixel(int x, int y)
{
	return screen[x][y];
}

void write_pixel(int x, int y, int color)
{
	screen[x][y] = color;
}

// 영역 채우기 알고리즘
void flood_fill(int x, int y)
{
	if (read_pixel(x, y) == WHITE)
	{
		write_pixel(x, y, BLACK);
		flood_fill(x - 1, y);
		flood_fill(x, y - 1);
		flood_fill(x + 1, y);
		flood_fill(x, y + 1);
	}
}
