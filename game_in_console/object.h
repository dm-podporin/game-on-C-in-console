#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>

/// Object related stuf

typedef struct SObject {
	int locY, locX;
	int pHeigh, pWidgh;
	int rightLimit, leftLimit, upperLimit, botomLimit;
	char icon[10][10];
	int status;
	int trackY, trackX;
} TObject;

BOOL IsCollisionObj(TObject obj1, TObject obj2, int dist)
{
	return ((obj1.locX + obj1.pWidgh + dist) > obj2.locX) && (obj1.locX < (obj2.locX + obj2.pWidgh + dist) &&
		((obj1.locY + obj1.pHeigh + dist) > obj2.locY) && (obj1.locY < (obj2.locY + obj2.pHeigh + dist)));
}

BOOL IsBorderCollision(TObject obj)
{
	return obj.locX == obj.leftLimit || obj.locX == obj.rightLimit ||
		obj.locY == obj.upperLimit || obj.locY == obj.botomLimit;
}

// draft for vector motion
//int locYM, locXM;
//float alfa;
//float speed;