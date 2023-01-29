#include "BrainSneak.h"

char BrainSneak::decide(COORD apple)
{
	COORD head = getHead();
	if (apple.X == head.X && apple.Y == head.Y)
		return 'n';


	if (apple.X == head.X && apple.Y > head.Y)
		return 'd';
	if (apple.X == head.X && apple.Y < head.Y)
		return 'u';

	if (apple.Y == head.Y && apple.X > head.X)
		return 'r';
	if (apple.Y == head.Y && apple.X < head.X)
		return 'l';

	if (apple.Y > head.Y && apple.X > head.X)
		return 'd';
	if (apple.Y < head.Y && apple.X < head.X)
		return 'u';

	if (apple.Y < head.Y && apple.X > head.X)
		return 'u';
	if (apple.Y > head.Y && apple.X > head.X)
		return 'd';

	if (apple.Y < head.Y && apple.X < head.X)
		return 'u';
	if (apple.Y > head.Y && apple.X < head.X)
		return 'd';

}

bool BrainSneak::compareCoordApple(COORD apple)
{
	return ((apple.X != arrX[length - 1]) && (apple.Y != arrY[length - 1]));
}

COORD BrainSneak::getHead()
{
	COORD head;
	head.X = arrX.back();
	head.Y = arrY.back();
	return head;
}

BrainSneak::BrainSneak(int widthWall, int heightWall)
{
	length = 1;
	this->widthWall = widthWall;
	this->heightWall = heightWall;

	arrX.push_back( widthWall / 2);
	arrY.push_back( heightWall / 2);
}

COORD BrainSneak::getTail()
{
	COORD Tail;
	Tail.X = arrX[0];
	Tail.Y = arrY[0];
	return Tail;
}

