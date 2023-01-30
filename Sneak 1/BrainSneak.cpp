#include "BrainSneak.h"

void BrainSneak::decide(COORD apple)
{
	COORD head = getHead();

	






	char choose;
	if (apple.X == head.X && apple.Y == head.Y)
		choose = 'n';


	if (apple.X == head.X && apple.Y > head.Y)
		choose = 'd';
	if (apple.X == head.X && apple.Y < head.Y)
		choose = 'u';

	if (apple.Y == head.Y && apple.X > head.X)
		choose = 'r';
	if (apple.Y == head.Y && apple.X < head.X)
		choose = 'l';

	if (apple.Y > head.Y)
		choose = 'd';
	if (apple.Y < head.Y)
		choose = 'u';

	bool rightChoose = true;
	int tdy;
	int tdx;
	int count = 0;
	do
	{

		if (rightChoose = false)
		{
			choose = 'n';
		}

		switch (choose) // пропускаем код нажатой клавиши внутрь оператора выбора
		{
		case 'd': // если была нажата клавиша вниз
			tdy = 1; // то приращение по оси ординат будет положительным
			tdx = 0; // по оси абсцисс приращение нулевое
			break;
		case 'u': // если вверх
			tdy = -1; // аналогично согласно геометрической логике
			tdx = 0;
			break;
		case 'l': // если влево
			tdy = 0;
			tdx = -1;
			break;
		case 'r': // если вправо
			tdy = 0;
			tdx = 1;
			break;
		case 'n': // если ничего
			break;
		}
		rightChoose = true;
		for (int i = 1; i < length; i++)
			if ((arrX.back() + tdx) == arrX[i] && (arrY.back() + tdy) == arrY[i]) // если совпадение найдено в цикле - прерываемся
				rightChoose = false;
		if (count == 100)
			throw BrainSneakEx();
		count++;

	} while (!rightChoose);

	switch (choose) // пропускаем код нажатой клавиши внутрь оператора выбора
	{
	case 'd': // если была нажата клавиша вниз
		dy = 1; // то приращение по оси ординат будет положительным
		dx = 0; // по оси абсцисс приращение нулевое
		break;
	case 'u': // если вверх
		dy = -1; // аналогично согласно геометрической логике
		dx = 0;
		break;
	case 'l': // если влево
		dy = 0;
		dx = -1;
		break;
	case 'r': // если вправо
		dy = 0;
		dx = 1;
		break;
	case 'n': // если ничего
		break;
	}
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
	dx = 1;
	dy = 0;
}

COORD BrainSneak::getTail()
{
	COORD Tail;
	Tail.X = arrX[0];
	Tail.Y = arrY[0];
	return Tail;
}

