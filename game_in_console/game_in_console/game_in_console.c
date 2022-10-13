#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#define mapWidth 8
#define mapHeight 7

// define map borders (game area = all area incide borders)

char map[mapHeight][mapWidth + 1];
int upperMB = 0;
int bottomMB = mapHeight - 1;
int leftMB = 0;
int rightMB = mapWidth - 1;

/// Personage related stuf

typedef struct SPersonage {
	int locY, locX;
	int pHeigh, pWidgh;
	int rightLimit, leftLimit, upperLimit, botomLimit;
} TPersonage;

TPersonage cat;
TPersonage mouse[1];

void InitPersonageT(TPersonage* pers, int yPos, int xPos, int pH, int pW)
{
	(*pers).locY = yPos;
	(*pers).locX = xPos;
	(*pers).pHeigh = pH;
	(*pers).pWidgh = pW;
	(*pers).leftLimit = leftMB;
	(*pers).rightLimit = mapWidth - pW;
	(*pers).upperLimit = upperMB;
	(*pers).botomLimit = mapHeight - pH;
}

//void ShowPers (TPersonage pers)
//{
//	for (char i = cat.locY, a = 0; i <= cat.locY + cat.pHeigh, a < cat.pHeigh; i++, a++)
//		for (char j = cat.locX, b = 0; i <= cat.locX + cat.pWidgh, b < cat.pWidgh; j++, b++)
//			map[i][j] = catIcon[a][b];
//}

BOOL IsCollisionPers(TPersonage pers1, TPersonage pers2)
{
	return ((pers1.locX + pers1.pWidgh) > pers2.locX) && (pers1.locX < (pers2.locX + pers2.pWidgh)) &&
		((pers1.locY + pers1.pHeigh) > pers2.locY) && (pers1.locY < (pers2.locY + pers2.pHeigh));
}

BOOL IsBorderCollision(TPersonage pers)
{
	return pers.locX == pers.leftLimit || pers.locX == pers.rightLimit ||
		pers.locY == pers.upperLimit || pers.locY == pers.botomLimit;
}

///Cursor handling

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


	//initialise cat

	InitPersonageT(&cat, 1, 1, 3, 5);
	
	char catIcon[3][5];

	sprintf(catIcon[0], "/|_/|");
	sprintf(catIcon[1], "|o.o|");
	sprintf(catIcon[2], "|_`_|");

	//initialise mouse[0]

	InitPersonageT(&mouse[0], 1, 1, 1, 1);

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

		if (IsBorderCollision(cat))
		{
			cat.locY = cat_track_y;
			cat.locX = cat_track_x;
		};

		//put cat on map

		for (char i = cat.locY, a = 0; i <= cat.locY + cat.pHeigh, a < cat.pHeigh; i++, a++)
			for (char j = cat.locX, b = 0; i <= cat.locX + cat.pWidgh, b < cat.pWidgh; j++, b++)
				map[i][j] = catIcon[a][b];

		//mouse[0] catch tracking and respawn

		if (IsCollisionPers(cat, mouse[0]))
		{
			do
			{
				mouse[0].locX = rand() % (rightMB - 2) + 1;
				mouse[0].locY = rand() % (bottomMB - 2) + 1;
			} while (IsCollisionPers(cat, mouse[0]));
			score++;
		}

		//mouse[0] movement

		int mouse_track_x = mouse[0].locX;
		int mouse_track_y = mouse[0].locY;

		do

		{
			mouseMovement = (rand() % 4);

			if (mouseMovement == 0) mouse[0].locY--;
				if (IsCollisionPers(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locY++;
			if (mouseMovement == 1) mouse[0].locY++;
				if (IsCollisionPers(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locY--;
			if (mouseMovement == 2) mouse[0].locX--;
				if (IsCollisionPers(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locX++;
			if (mouseMovement == 3) mouse[0].locX++;
				if (IsCollisionPers(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locX--;

		} while (mouse[0].locX == mouse_track_x && mouse[0].locY == mouse_track_y);

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
