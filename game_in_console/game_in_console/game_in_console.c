#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>


int main()

{

	char map[20][40];
	int i;
	int cat_x = 10, cat_y = 5;
	int mouse_x = 7, mouse_y = 7;
	int mouseMovement;
	char key;

	srand(time(0));

	do

	{

		sprintf(map[0], "---------------------------------------");

		for (i = 1; i < 19; i++)
			sprintf(map[i], "|                                     |");

		sprintf(map[19], "---------------------------------------");

		map[cat_y][cat_x] = 'X';
		map[mouse_y][mouse_x] = '@';

		key = _getch();

		system("cls");
		for (i = 0; i < 20; i++)
			printf("%s\n", map[i]);

		//cat movement

		int cat_track_x = cat_x;
		int cat_track_y = cat_y;

		if (key == 'w') cat_y--;
		if (key == 's') cat_y++;
		if (key == 'a') cat_x--;
		if (key == 'd') cat_x++;

		if (map[cat_y][cat_x] == '|' || map[cat_y][cat_x] == '-')
		{ 
			cat_y = cat_track_y;
			cat_x = cat_track_x;
		};

		//mouse movement


		mouseMovement = (rand() % 20);

		if (mouseMovement < 6) mouse_y --;
		if (mouseMovement < 11 & 5 < mouseMovement) mouse_y ++;
		if (mouseMovement < 16 & 10 < mouseMovement) mouse_x --;
		if (15 < mouseMovement) mouse_x ++;


		printf("mouse movement and location");

		{
			printf("%i,% i,%i ", mouseMovement, mouse_y, mouse_x);
		}

		printf("\n");
	}

	while (key != 'e');


	return 0;

}
