#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()

{

	char mas[20][40];
	int i;
	int x = 10, y = 5;
	char key;


	do

	{

		sprintf(mas[0], "---------------------------------------");

		for (i = 1; i < 19; i++)
			sprintf(mas[i], "|                                     |");

		sprintf(mas[19], "---------------------------------------");

		mas[y][x] = 'X';

		key = _getch();

		system("cls");
		for (i = 0; i < 20; i++)
			printf("%s\n", mas[i]);

		if (key == 'w') y--;
		if (key == 's') y++;
		if (key == 'a') x--;
		if (key == 'd') x++;
	}

	while (key != 'e');


	return 0;

}
