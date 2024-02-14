#include "BrainSneak.h"

void BrainSneak::decide(COORD apple)
{
	COORD head = getHead();
	
	char lastChoose;// узнаем какой был последний выбор
	if (dy == 1)
		lastChoose = 'd';
	if (dx == 1)
		lastChoose = 'r';
	if (dy == -1)
		lastChoose = 'u';
	if (dx == -1)
		lastChoose = 'l';




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
		if (rightChoose == false && count == 1)
			choose = 'd';
		if (rightChoose == false && count == 2)
			choose = 'u';
		if (rightChoose == false && count == 3)
			choose = 'r';
		if (rightChoose == false && count == 4)
			choose = 'l';
		if (rightChoose == false && count == 5)
			choose = 'n';

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
			tdy = dy;
			tdx = dx;
			break;
		}
		rightChoose = true;
		for (int i = 1; i < length; i++)
		{
			int r = arrX.back() + tdx;
			int rr = arrX[i];
			if ((r == rr) && ((arrY.back() + tdy) == arrY[i])) // если совпадение найдено в цикле - прерываемся
				rightChoose = false;
		}
			if (count == 100)
			throw BrainSneakEx();
		++count;

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

void BrainSneak::usersDecide(int k)
{
	switch (k) // пропускаем код нажатой клавиши внутрь оператора выбора
	{
	case 80: // если была нажата клавиша вниз
		dy = 1; // то приращение по оси ординат будет положительным
		dx = 0; // по оси абсцисс приращение нулевое
		break;
	case 72: // если вверх
		dy = -1; // аналогично согласно геометрической логике
		dx = 0;
		break;
	case 75: // если влево
		dy = 0;
		dx = -1;
		break;
	case 77: // если вправо
		dy = 0;
		dx = 1;
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

void BrainSneak::decide2(COORD apple)
{
	COORD head = getHead();

	char lastChoose;// узнаем какой был последний выбор
	if (dy == 1)
		lastChoose = 'd';
	if (dx == 1)
		lastChoose = 'r';
	if (dy == -1)
		lastChoose = 'u';
	if (dx == -1)
		lastChoose = 'l';

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
		if (rightChoose == false && count == 1)
			choose = 'd';
		if (rightChoose == false && count == 2)
			choose = 'u';
		if (rightChoose == false && count == 3)
			choose = 'r';
		if (rightChoose == false && count == 4)
			choose = 'l';
		if (rightChoose == false && count == 5)
			choose = 'n';

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
			tdy = dy;
			tdx = dx;
			break;
		}
		rightChoose = true;
		for (int i = 1; i < length; i++)
		{
			int r = arrX.back() + tdx;
			int rr = arrX[i];
			if ((r == rr) && ((arrY.back() + tdy) == arrY[i])) // если совпадение найдено в цикле - прерываемся
				rightChoose = false;
		}
		if (count == 100)
			throw BrainSneakEx();
		++count;

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
