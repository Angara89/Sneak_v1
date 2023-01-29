#pragma once 
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include "BrainSneak.h"
using namespace std;

const int width = 50, height = 30;	 // ������� ����, �� �������� ������ ������


void setObject(const HANDLE& h, const COORD &coord, const char &simbol, const int &color = 10)
{
	SetConsoleCursorPosition(h, coord); // ���������� ������ �� ������� "������"
	SetConsoleTextAttribute(h, color); // ������������� ������� ���� ��� ��������� "������"
	putchar(simbol);
}

int main()
{
	cout << "Choose mode (auto - 'a', manual - 'm') " << endl; 
	char choose = 'm';
	cin >> choose;
	system("cls");
	srand(time(0)); // ������ ���������� ��������� �����
	rand(); // �������� ��� ���������� �������� �����
	system("mode con cols=51 lines=31"); // ��������� �������� ���� �������
	MoveWindow(GetConsoleWindow(), 50, 50, 600, 600, true); // ��������� ��������� ������� ���� ������� (50 � 50 - ��� �������
	// ������������ �������� ������ ���� ��������
	int dx = 1, dy = 0; // �������� �������� �� ���� ��� �������� "������"
	COORD apple;
	BrainSneak Brain(width, height);
	do // ���� ������ ���������� ������ �������� ������� - �� ����� ��� �� ��������� �� "�������"
	{
		apple.X = rand() % (width - 2) + 1;
		apple.Y = rand() % (height - 2) + 1;
	} while (Brain.compareCoordApple(apple));

	int sleep_time = 100; // ���������� ������� ������ 

	char snake = '*'; // ������ ��� ����������� ���� "������"
	char appleSimbol = 'o'; // ������ ��� ����������� "������"
	char head = 1; // ������ ��� ����������� ������ "������"

	COORD c; // ������ ��� �������� ���������
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ������ ������ ������
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), false }; // �������� ���������� �� ����������� �������
	SetConsoleCursorInfo(h, &cci); //���������� ���������� � ������
	SetConsoleTextAttribute(h, 4); // ��������� �����, ������� �������� ����� ����
	for (int y = 0; y < height; y++) // ����������� ������� ���� �� ��������� �����
	{
		for (int x = 0; x < width; x++)
		{
			char s;
			if (x == 0 && y == 0) // � ������� ����� ���� ���� - ������ ���������������� ����
				s = 218;
			else if (x == 0 && y == height - 1) // ������ ����� ����
				s = 192;
			else if (y == 0 && x == width - 1) // ������� ������ ����
				s = 191;
			else if (y == height - 1 && x == width - 1) // ������ ������ ����
				s = 217;
			else if (y == 0 || y == height - 1) // ������� � ������ ������� ����
				s = 196;
			else if (x == 0 || x == width - 1) // ����� � ������ ������� ����
				s = 179;
			else s = ' '; // �� ���� ��������� ������� ������ ���� ������ ������ (�������� ������ ������� ����)
			putchar(s); // ������� ������
		}
		cout << endl;
	}
	setObject(h, apple, appleSimbol, 12); //������������� ������ �� ��� ��������� �����
	setObject(h, Brain.getHead(), head, 10); //������������� ������ ������

	bool flag = true; // ���������� ��� ���������� ����� �����
	do // ���������� ���� ����
	{
		Sleep(sleep_time); // �������� ������ ��������� �� �������� ����� ��������

		if (_kbhit() && choose == 'm') // ���������, ���� �� ������ �����-���� ������� � ��������� � ��������� � ������ ������
		{
			int k = _getch(); // ��������� ��� ������� �� ������
			if (k == 0 || k == 224) // ���� ������ ��� - ���������������, ��������� ������ ���
				k = _getch();
			switch (k) // ���������� ��� ������� ������� ������ ��������� ������
			{
			case 80: // ���� ���� ������ ������� ����
				dy = 1; // �� ���������� �� ��� ������� ����� �������������
				dx = 0; // �� ��� ������� ���������� �������
				break;
			case 72: // ���� �����
				dy = -1; // ���������� �������� �������������� ������
				dx = 0;
				break;
			case 75: // ���� �����
				dy = 0;
				dx = -1;
				break;
			case 77: // ���� ������
				dy = 0;
				dx = 1;
				break;
			case 27: // ���� ���� ������ ������� ESC
				flag = false; // ������������� ������ �� ����, ���� ��������� ����� ��������
				break;
			}
		}
		else
		{
			char k = Brain.decide(apple);
			switch (k) // ���������� ��� ������� ������� ������ ��������� ������
			{
			case 'd': // ���� ���� ������ ������� ����
				dy = 1; // �� ���������� �� ��� ������� ����� �������������
				dx = 0; // �� ��� ������� ���������� �������
				break;
			case 'u': // ���� �����
				dy = -1; // ���������� �������� �������������� ������
				dx = 0;
				break;
			case 'l': // ���� �����
				dy = 0;
				dx = -1;
				break;
			case 'r': // ���� ������
				dy = 0;
				dx = 1;
				break;
			case 'n': // tckb ybxtuj nj
				break;
			}
		}

		int X = Brain.arrX.back() + dx; // ���������� �������� �������� ������ "������" ����� ��������
		int Y = Brain.arrY.back() + dy; // �� �� ����� ��� ��������
		if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) // �������� �� ���������� ������ ����
		{
			flag = false; // ���� ��� - ������ ��������� ����������� ���������� ����� 
		}
		else if (X == apple.X && Y == apple.Y) // �������� �� ���������� "������"
		{
			setObject(h, Brain.getHead(), snake, 10);

			Brain.length++; // ���������� ����� "������" (������ ����������)
			Brain.arrX.push_back(X) ; // ��������� � ������� ������� ������ ����� "������"
			Brain.arrY.push_back(Y) ; // ��������� � ������� ������� ������ ����� "������"
			setObject(h, Brain.getHead(), head, 10);

			if (Brain.length == max_length) // ��������, �������� �� ����� "������" ������ ������������� ��������
			{
				break; // ���� ��� - ������ ��������� ���� 
			}

			int i; // ���������� ��� �������� ���������� ������� "������", �� ����������� � �������� "������"
			do
			{
				apple.X = rand() % (width - 2) + 1; // ��������� ����� ��������� "������"
				apple.Y = rand() % (height - 2) + 1;
				i = 0; // ��������� ����� ������������� ���������
				for (; i < Brain.length; i++) // ������ ����� �� ������ ����������
					if (apple.X == Brain.arrX[i] && apple.Y == Brain.arrY[i]) // ���� ���������� �������
						break; // �� ��������� ���� for
			} while (i < Brain.length); // ����� ����� ��������� ������������, ���� ����� ������������� ��������� ������ ����� "������"
			setObject(h, apple, appleSimbol, 12); //������������� ������ �� ��� ��������� �����
		}
		else // ������, ����� ������ "������" ��������� �� ����� ������ �������
		{
			int i = 1; // ���������� �� ���������� �������, �� ����������� � ����� �������� - ����� ������ "������"
			for (; i < Brain.length; i++)
				if (X == Brain.arrX[i] && Y == Brain.arrY[i]) // ���� ���������� ������� � ����� - �����������
					break;
			if (i < Brain.length) // ���� ����� ������������� ������� ������ ����� "������" - �� ��������� �������� ���� ����
			{
				//break;
			}
			else // � ����� ��������� ��������� ������ "������"
			{
				setObject(h, Brain.getTail(), ' '); // ����� �� ����� ������ ������
				if (Brain.length > 1) // ���� ����� ������ ������ 
				{
					setObject(h, Brain.getHead(), snake); // ����� �� ����� ������ ������ ���� ������
				}

				for (int i = 0; i < Brain.length - 1; i++) // ��������� ���� ������ ��������� ������� "������"
				{
					Brain.arrX[i] = Brain.arrX[i + 1]; // ������������ ��� ������ - ����� ����������
					Brain.arrY[i] = Brain.arrY[i + 1];
				}

				Brain.arrX[Brain.length - 1] = X; // ������������� ����� ������� ������ "������"
				Brain.arrY[Brain.length - 1] = Y;
				setObject(h, Brain.getHead(), head, 10);
			}
		}
	} while (flag); // ������� �� �����, ���� �������� ����������� ����������
	system("cls"); // ������� �����
	cout << "GAME OVER\n"; // ������� ��������� � ����� ����
	system("pause");
}