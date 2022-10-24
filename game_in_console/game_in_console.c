#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include "object.h"
#include "cursorHandling.h"

#define mapWidth 120
#define mapHeight 55
#define mouseNumber 10
#define trapNumber 50
#define mouseHNumber 35

// define map borders (game area = all area incide borders)

char map[mapHeight][mapWidth + 1];
int upperMB = 0;
int bottomMB = mapHeight - 1;
int leftMB = 0;
int rightMB = mapWidth - 1;

/// Object related stuf


TObject cat;
TObject mouse[mouseNumber];
TObject mouseHole[mouseHNumber];
TObject mouseTrap[trapNumber];

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
	(*obj).trackY = 0;
	(*obj).trackX = 0;
}

void RandomRespLoc(TObject *obj, TObject *col1, int colArea)
{
	do
	{
		(*obj).locX = rand() % (rightMB - 2) + 1;
		(*obj).locY = rand() % (bottomMB - 2) + 1;
	} while (IsCollisionObj(*obj, *col1, colArea));
	}

// put ibject on map

void PutObject(TObject *obj)
	{
	for (char i = (*obj).locY, a = 0; i < ((*obj).locY + (*obj).pHeigh), a < (*obj).pHeigh; i++, a++)
	for (char j = (*obj).locX, b = 0; i < ((*obj).locX + (*obj).pWidgh), b < (*obj).pWidgh; j++, b++)
	map[i][j] = (*obj).icon[a][b];
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
	int mouseMovement;
	char key = 0;
	int score = 0;
	int holeCollis = 0;
	int trapMouse = 0;
	int trapCat = 0;
	int catLive = 5;
	int mouseUnMove = 0;
	char randomHole;
	char level = 0;


	srand(time(0));

	// mouse holes creation

	for (char i = 0; i < mouseHNumber; i++)
	{
		InitObject(&mouseHole[i], rand() % (bottomMB - 2) + 1, rand() % (rightMB - 2) + 1, 1, 1);
		sprintf(mouseHole[i].icon[0], "0");
	}

	// trap creation

	for (char i = 0; i < trapNumber; i++)
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


	for (char i = 0; i < mouseNumber; i++)
	{
		InitObject(&mouse[i], rand() % (bottomMB - 2) + 1, rand() % (rightMB - 2) + 1, 1, 2);
		sprintf(mouse[i].icon[0], "<~");
	}

	do

	{
		if (level == 0)
		{
			setcur(0, 0);
			hidecursor();
			printf("Welcome to ""Catch mouse game"". In thia game you play as a cat who need to catch as much mouse as it can\n");
			printf("Before launching this game please change you console to have Window more then 120x57 (Width/Height), so game will work correctly\n");
			Sleep(1500);
			printf("\n");
			printf("Use W A S D to move your cat\n");
			Sleep(1500);
			printf("Be careful traps _/ might damage you cat\n");
			Sleep(1500);
			printf("Mouse can go to any mouse hole and apear from any another mouse hole\n");
			Sleep(1500);
			printf("Good luck\n");
			Sleep(1500);
			printf("Press Q to start\n");

			if (GetKeyState('Q') < 0)
			{
				level = 1;
				system("cls");

			};
		}

		if (level == 1)

		{

			// empty map creation

			mapCreation();

			//mouse holes putting on map

			for (char i = 0; i < mouseHNumber; i++)
			{
				PutObject(&mouseHole[i]);
			}

			//mouse trap putting on map

			for (char i = 0; i < trapNumber; i++)
			{
				PutObject(&mouseTrap[i]);
			}

			//cat

			cat.trackX = cat.locX;
			cat.trackY = cat.locY;

			if (GetKeyState('W') < 0) cat.locY--;
			if (GetKeyState('S') < 0) cat.locY++;
			if (GetKeyState('A') < 0) cat.locX--;
			if (GetKeyState('D') < 0) cat.locX++;

			// border tracking for cat

			if (IsBorderCollision(cat))
			{
				cat.locY = cat.trackY;
				cat.locX = cat.trackX;
			};

			//mouses catch tracking and respawn

			for (char i = 0; i < mouseNumber; i++)
			{
				if (IsCollisionObj(cat, mouse[i], 0))
				{
					do
					{
						mouse[i].locX = rand() % (rightMB - 2) + 1;
						mouse[i].locY = rand() % (bottomMB - 2) + 1;
					} while (IsCollisionObj(cat, mouse[i], 1));
					score++;
				}
			}

			//mouse[0] movement

			for (char i = 0; i < mouseNumber; i++)
			{
				mouse[i].trackX = mouse[i].locX;
				mouse[i].trackY = mouse[i].locY;
			}

			do

			{
				for (char i = 0; i < mouseNumber; i++)

				{
					mouseMovement = (rand() % 4);
					if (mouseMovement == 0) mouse[i].locY--;
					if (mouseMovement == 1) mouse[i].locY++;
					if (mouseMovement == 2) mouse[i].locX--;
					if (mouseMovement == 3) mouse[i].locX++;
				}

				// mouse hole collision

				for (char i = 0; i < mouseHNumber; i++)
				{
					for (char j = 0; j < mouseHNumber; j++)
					{
						if (IsCollisionObj(mouseHole[i], mouse[j], 0))
							holeCollis++,
							randomHole = (rand() % mouseHNumber),
							mouse[j].locX = mouseHole[randomHole].locX,
							mouse[j].locY = mouseHole[randomHole].locY,
							randomHole = 0;
					}
				}

				for (char i = 0; i < mouseNumber; i++)
				{
					if ((IsCollisionObj(cat, mouse[i], 0)) || IsBorderCollision(mouse[i])) mouse[i].locX = mouse[i].trackX, mouse[i].locY = mouse[i].trackY;

				}


				// trap track

				for (char i = 0; i < trapNumber; i++)
				{

					//trap actuation

					if (mouseTrap[i].status == 0)
					{
						for (char j = 0; j < mouseNumber; j++)
						{
							if (IsCollisionObj(mouseTrap[i], mouse[j], 0))
							{
								trapMouse++,
									mouse[j].locX = rand() % (rightMB - 2) + 1, mouse[j].locY = rand() % (bottomMB - 2) + 1;
								mouseTrap[i].status = 1;
							}
						}

						if (IsCollisionObj(mouseTrap[i], cat, 0))
						{
							trapCat++,
								catLive--,
								cat.locY = cat.trackY;
							cat.locX = cat.trackX;
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
				for (char i = 0; i < mouseNumber; i++)
				{
					if (mouse[i].locX == mouse[i].trackX && mouse[i].locY == mouse[i].trackY) mouseUnMove++;
				}

			} while (mouseUnMove < 0);

			mouseUnMove = 0;

			for (char i = 0; i < mouseNumber; i++)
			{
				PutObject(&mouse[i]);
			}

			//put cat on map

			PutObject(&cat);

			//printing

			setcur(0, 0);
			hidecursor();
			printf("Mouse caught %i; cat health %i \n", score, catLive);
			showMap();
			//printf("Collisions: hole - %i; tCat - %i; tMouse %i \n", holeCollis, trapCat, trapMouse);
			//printf("Mouse movement and location %i,% i,%i \n", mouseMovement, mouse[0].locY, mouse[0].locX);
			//printf("Cat movement and location %i,%i \n", cat.locY, cat.locX);
			Sleep(45);
			if (catLive <= 0) level = 99;
		}

		if (level == 99)
		{
			if (key == 0)
				{
				system("cls");
				key++;
			}
			setcur(0, 0);
			hidecursor();
			printf("Your cat is out of heals, Your score %i \n", score);
			printf("Press R to restart\n");
			if (GetKeyState('R') < 0)
			{
				level = 1;
				catLive = 5;
				score = 0;
				system("cls");
				key = 0;
			}
		}

	}

	while (GetKeyState(VK_ESCAPE) >= 0);

	return 0;


}

