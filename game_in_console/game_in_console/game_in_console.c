﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#define mapWidth 20
#define mapHeight 10

// define map borders (game area = all area incide borders)

char map[mapHeight][mapWidth + 1];

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

// put cursor to the begining of the concole (to use instead of syst(cls) to remove 
void setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/// Map related stuf

void mapCreation()
{
	for (int i = 0; i < mapWidth; i++)
		map[0][i] = '-';
	map[0][mapWidth] = '\0';

	for (int i = 1; i < mapWidth - 1; i++)
		map[1][i] = ' ';
	map[1][0] = '|';
	map[1][mapWidth - 1] = '|';
	map[1][mapWidth] = '\0';

	for (int i = 1; i < mapHeight - 1; i++)
		strncpy(map[i], map[1],mapWidth + 1);

	strncpy(map[mapHeight - 1], map[0], mapWidth + 1);
}

void showMap()
{
		for (int i = 0; i < mapHeight; i++)
		printf("%s\n", map[i]);
}

int main()

{
	srand(time(0));
	int i;
	int mouseMovement;
	char key;
	int score = 0;


	int topMB = 0;
	int bottomMB = mapHeight - 1;
	int leftMB = 0;
	int rightMB = mapWidth - 1;

	//initialise cat and mouse

	int cat_x = (rand() % (rightMB - 2) + 1), cat_y = rand() % (bottomMB - 2) + 1;
	int mouse_x = (rand() % (rightMB - 2) + 1), mouse_y = rand() % (bottomMB - 2) + 1;

	int mouseMovement;
	char key;
	int score = 0;


	mouse[0].locX = rand() % (rightMB - 2) + 1;
	mouse[0].locY = rand() % (bottomMB - 2) + 1;

	do

	{
		// empty map creation

		mapCreation();

		key = _getch();

		//cat

		int cat_track_x = cat.locX;
		int cat_track_y = cat.locY;

		if (key == 'w') cat.locY--;
		if (key == 's') cat.locY++;
		if (key == 'a') cat.locX--;
		if (key == 'd') cat.locX++;

		// border tracking for cat

		if (map[cat_y][cat_x] == '|' || map[cat_y][cat_x] == '-')
		{
			cat.locY = cat_track_y;
			cat.locX = cat_track_x;
		};

		//mouse catch tracking and respawn

		if (cat_y == mouse_y && cat_x == mouse_x)
		{
			mouse_x = rand() % (rightMB-2) + 1;
			mouse_y = rand() % (bottomMB-2) + 1;
			score++;
		}

		//mouse[0] movement

		int mouse_track_x = mouse[0].locX;
		int mouse_track_y = mouse[0].locY;

		do

		{
			mouseMovement = (rand() % 4);

			if (mouseMovement == 0 && mouse_y > 1 && !((mouse_y -1 == cat_y) && mouse_x == cat_x)) mouse_y--;
			if (mouseMovement == 1 && (mouse_y < (bottomMB-1)) && !((mouse_y + 1 == cat_y) && mouse_x == cat_x)) mouse_y++;
			if (mouseMovement == 2 && mouse_x > 1 && !((mouse_x - 1 == cat_x) && mouse_y == cat_y)) mouse_x--;
			if (mouseMovement == 3 && (mouse_x < (rightMB -2)) && !((mouse_x + 1 == cat_x) && mouse_y == cat_y)) mouse_x++;

		} while (mouse_y < 1 || 
			mouse_y > bottomMB || mouse_x < 1 || mouse_x > rightMB || (mouse_x == mouse_track_x && mouse_y == mouse_track_y) || (cat_y == mouse_y && cat_x == mouse_x));

		map[mouse[0].locY][mouse[0].locX] = 'Q';

		//printing

		setcur(0, 0);
		hidecursor();
		showMap();
		printf("Mouse caught %i \n", score);
		printf("Mouse movement and location %i,% i,%i \n", mouseMovement, mouse[0].locY, mouse[0].locX);
		printf("Cat movement and location % i,%i \n", cat.locY, cat.locX);
		Sleep(35);
	}

	while (key != 'e');

	return 0;

}
