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

/// Object related stuf

typedef struct SObject {
	int locY, locX;
	int pHeigh, pWidgh;
	int rightLimit, leftLimit, upperLimit, botomLimit;
} TObject;

TObject cat;
TObject mouse[1];

void InitObjectT(TObject* obj, int yPos, int xPos, int pH, int pW)
{
	(*obj).locY = yPos;
	(*obj).locX = xPos;
	(*obj).pHeigh = pH;
	(*obj).pWidgh = pW;
	(*obj).leftLimit = leftMB;
	(*obj).rightLimit = mapWidth - pW;
	(*obj).upperLimit = upperMB;
	(*obj).botomLimit = mapHeight - pH;
}

//void ShowObj (TObject obj)
//{
//	for (char i = cat.locY, a = 0; i <= cat.locY + cat.pHeigh, a < cat.pHeigh; i++, a++)
//		for (char j = cat.locX, b = 0; i <= cat.locX + cat.pWidgh, b < cat.pWidgh; j++, b++)
//			map[i][j] = catIcon[a][b];
//}

BOOL IsCollisionObj(TObject obj1, TObject obj2)
{
	return ((obj1.locX + obj1.pWidgh) > obj2.locX) && (obj1.locX < (obj2.locX + obj2.pWidgh)) &&
		((obj1.locY + obj1.pHeigh) > obj2.locY) && (obj1.locY < (obj2.locY + obj2.pHeigh));
}

BOOL IsBorderCollision(TObject obj)
{
	return obj.locX == obj.leftLimit || obj.locX == obj.rightLimit ||
		obj.locY == obj.upperLimit || obj.locY == obj.botomLimit;
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
		strncpy(map[i], map[1], mapWidth + 1);

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

	InitObjectT(&cat, 1, 1, 3, 5);

	char catIcon[3][5];

	sprintf(catIcon[0], "/|_/|");
	sprintf(catIcon[1], "|o.o|");
	sprintf(catIcon[2], "|_`_|");

	//initialise mouse[0]

	InitObjectT(&mouse[0], 1, 1, 1, 1);

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

		if (IsCollisionObj(cat, mouse[0]))
		{
			do
			{
				mouse[0].locX = rand() % (rightMB - 2) + 1;
				mouse[0].locY = rand() % (bottomMB - 2) + 1;
			} while (IsCollisionObj(cat, mouse[0]));
			score++;
		}

		//mouse[0] movement

		int mouse_track_x = mouse[0].locX;
		int mouse_track_y = mouse[0].locY;

		do

		{
			mouseMovement = (rand() % 4);

			if (mouseMovement == 0) mouse[0].locY--;
			if (IsCollisionObj(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locY++;
			if (mouseMovement == 1) mouse[0].locY++;
			if (IsCollisionObj(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locY--;
			if (mouseMovement == 2) mouse[0].locX--;
			if (IsCollisionObj(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locX++;
			if (mouseMovement == 3) mouse[0].locX++;
			if (IsCollisionObj(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locX--;

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