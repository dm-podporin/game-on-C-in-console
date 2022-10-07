#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>


int main()

{
	srand(time(0));

	enum { map_rows = 10, map_columns = 10 };

	char map[map_rows][map_columns];
	int i;

	// define map borders (game area = all area incide borders)

	int topMB = 0;
	int bottomMB = map_rows - 1;
	int leftMB = 0;
	int rightMB = map_columns - 1;

	//inotialise cat and mouse

	int cat_x = (rand() % (rightMB - 2) + 1), cat_y = rand() % (bottomMB - 2) + 1;
	int mouse_x = (rand() % (rightMB - 2) + 1), mouse_y = rand() % (bottomMB - 2) + 1;

	int mouseMovement;
	char key;
	int score = 0;


	do

	{
		// empty map creation

		sprintf(map[topMB], "---------");

		for (i = topMB+1; i < bottomMB; i++)
			sprintf(map[i], "|       |");

		sprintf(map[bottomMB], "---------");

		key = _getch();

		//cat movement

		int cat_track_x = cat_x;
		int cat_track_y = cat_y;

		if (key == 'w') cat_y--;
		if (key == 's') cat_y++;
		if (key == 'a') cat_x--;
		if (key == 'd') cat_x++;

		// border tracking for cat

		if (map[cat_y][cat_x] == '|' || map[cat_y][cat_x] == '-')
		{
			cat_y = cat_track_y;
			cat_x = cat_track_x;
		};

		//mouse catch tracking

		if (cat_y == mouse_y && cat_x == mouse_x)
		{
			mouse_x = rand() % (rightMB-2) + 1;
			mouse_y = rand() % (bottomMB-2) + 1;
			score++;
		}

		//mouse movement

		int mouse_track_x = mouse_x;
		int mouse_track_y = mouse_y;

		do

		{
			mouseMovement = (rand() % 4);

			if (mouseMovement == 0 && mouse_y > 1 && !((mouse_y -1 == cat_y) && mouse_x == cat_x)) mouse_y--;
			if (mouseMovement == 1 && (mouse_y < (bottomMB-1)) && !((mouse_y + 1 == cat_y) && mouse_x == cat_x)) mouse_y++;
			if (mouseMovement == 2 && mouse_x > 1 && !((mouse_x - 1 == cat_x) && mouse_y == cat_y)) mouse_x--;
			if (mouseMovement == 3 && (mouse_x < (rightMB -2)) && !((mouse_x + 1 == cat_x) && mouse_y == cat_y)) mouse_x++;

		} while (mouse_y < 1 || mouse_y > bottomMB || mouse_x < 1 || mouse_x > rightMB || (mouse_x == mouse_track_x && mouse_y == mouse_track_y) || (cat_y == mouse_y && cat_x == mouse_x));

		map[cat_y][cat_x] = 'Q';
		map[mouse_y][mouse_x] = '*';

		//printing

		system("cls");
		for (i = 0; i < 20; i++)
			printf("%s\n", map[i]);
		printf("Mouse caught %i \n", score);
		printf("Mouse movement and location %i,% i,%i \n", mouseMovement, mouse_y, mouse_x);
		printf("Cat movement and location % i,%i \n", cat_y, cat_x);

	}

	while (key != 'e');

	return 0;

}
