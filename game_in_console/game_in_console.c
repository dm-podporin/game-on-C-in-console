#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#define mapWidth 50
#define mapHeight 24

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
	char icon[10][10];
	int status;
} TObject;

TObject cat;
TObject mouse[1];
TObject mouseHole[10];
TObject mouseTrap[10];

void InitObject(TObject *obj, int yPos, int xPos, int pH, int pW)
{
	(*obj).locY = yPos;
	(*obj).locX = xPos;
	(*obj).pHeigh = pH;
	(*obj).pWidgh = pW;
	(*obj).leftLimit = leftMB;
	(*obj).rightLimit = mapWidth - pW;
	(*obj).upperLimit = upperMB;
	(*obj).botomLimit = mapHeight - pH;
	(*obj).icon[10][10];
	(*obj).status = 0;
}


// put ibject on map

void PutObject(TObject *obj)
	{
	for (char i = (*obj).locY, a = 0; i < ((*obj).locY + (*obj).pHeigh), a < (*obj).pHeigh; i++, a++)
	for (char j = (*obj).locX, b = 0; i < ((*obj).locX + (*obj).pWidgh), b < (*obj).pWidgh; j++, b++)
	map[i][j] = (*obj).icon[a][b];
	}


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

	// mouse holes creation

	for (i = 0; i < 10; i++)
	{
		InitObject(&mouseHole[i], rand() % (bottomMB - 2) + 1, rand() % (rightMB - 2) + 1, 1, 1);
		sprintf(mouseHole[i].icon[0], "0");
	}

	// trap creation

	for (i = 0; i < 10; i++)
	{
		InitObject(&mouseTrap[i], rand() % (bottomMB - 2) + 1, rand() % (rightMB - 2) + 1, 1, 2);
		sprintf(mouseTrap[i].icon[0], "_/");
	}

	//initialise cat

	InitObject(&cat, 1, 1, 3, 5);

	sprintf(cat.icon[0], "/|_/|");
	sprintf(cat.icon[1], "|o.o|");
	sprintf(cat.icon[2], "|_`_|");

	//initialise mouse[0]

	InitObject(&mouse[0], 1, 1, 1, 2);
	sprintf(mouse[0].icon[0], "<~");

	mouse[0].locX = rand() % (rightMB - 2) + 1;
	mouse[0].locY = rand() % (bottomMB - 2) + 1;

	int holeCollis = 0; 
	int trapMouse = 0;
	int trapCat = 0;
	int catLive = 5;

	do

	{
		// empty map creation

		mapCreation();

		//mouse holes putting on map

		for (i = 0; i < 10; i++)
		{
			PutObject(&mouseHole[i]);
		}

		//mouse trap putting on map

		for (i = 0; i < 10; i++)
		{
			PutObject(&mouseTrap[i]);
		}

		//cat

		int cat_track_x = cat.locX;
		int cat_track_y = cat.locY;

		if (GetKeyState('W') < 0) cat.locY--;
		if (GetKeyState('S') < 0) cat.locY++;
		if (GetKeyState('A') < 0) cat.locX--;
		if (GetKeyState('D') < 0) cat.locX++;

		// border tracking for cat

		if (IsBorderCollision(cat))
		{
			cat.locY = cat_track_y;
			cat.locX = cat_track_x;
		};

		//put cat on map

		PutObject(&cat);

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
			if (mouseMovement == 1) mouse[0].locY++;
			if (mouseMovement == 2) mouse[0].locX--;
			if (mouseMovement == 3) mouse[0].locX++;
			
			// mouse holes collision

			for(i = 0; i < 10; i++)
			{
				if (IsCollisionObj(mouseHole[i], mouse[0])) holeCollis++, mouse[0].locX = mouseHole[rand() % 10].locX, mouse[0].locY = mouseHole[rand() % 10].locY + 1;
			}	for(i = 0; i < 10; i++)
			{
				if (IsCollisionObj(mouseHole[i], mouse[0])) holeCollis++, mouse[0].locX = mouseHole[rand() % 10].locX, mouse[0].locY = mouseHole[rand() % 10].locY + 1;
			}
			if (IsCollisionObj(cat, mouse[0]) || IsBorderCollision(mouse[0])) mouse[0].locX = mouse_track_x, mouse[0].locY = mouse_track_y;

			// mouse trap collision

			for (i = 0; i < 10; i++)
			{

				// trap actuation

				if (mouseTrap[i].status == 0)
				{
						if (IsCollisionObj(mouseTrap[i], mouse[0]))
					{
						trapMouse++,
						mouse[0].locX = rand() % (rightMB - 2) + 1, mouse[0].locY = rand() % (bottomMB - 2) + 1;
						mouseTrap[i].status = 1;
					}

					if (IsCollisionObj(mouseTrap[i], cat))
					{
						trapCat++,
						catLive --,
						cat.locY = cat_track_y;
						cat.locX = cat_track_x;
						mouseTrap[i].status = 1;
					}
				}

				// trap tracking

				if (mouseTrap[i].status > 0)
				{
					map[mouseTrap[i].locY][mouseTrap[i].locX] = "X";
					mouseTrap[i].status++;
					if (mouseTrap[i].status == 50)
					{
						mouseTrap[i].locX = rand() % (rightMB - 2) + 1, mouseTrap[i].locY = rand() % (bottomMB - 2) + 1;
						mouseTrap[i].status = 0;
					}

			}
			}

		} while (mouse[0].locX == mouse_track_x && mouse[0].locY == mouse_track_y);

		PutObject(&mouse);

		//printing

		setcur(0, 0);
		hidecursor();
		printf("Mouse caught %i; cat health %i \n", score, catLive);
		showMap();
		printf("Collisions: hole - %i; tCat - %i; tMouse %i \n", holeCollis, trapCat, trapMouse);
		printf("Mouse movement and location %i,% i,%i \n", mouseMovement, mouse[0].locY, mouse[0].locX);
		printf("Cat movement and location %i,%i \n", cat.locY, cat.locX);
		Sleep(55);
	}

	while (GetKeyState(VK_ESCAPE) >= 0);

	return 0;

}