#pragma once 
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include "BrainSneak.h"
using namespace std;

const int width = 50, height = 30;	 // размеры поля, по которому бегает змейка


void setObject(const HANDLE& h, const COORD &coord, const char &simbol, const int &color = 10)
{
	SetConsoleCursorPosition(h, coord); // отправляем курсор на позицию "яблока"
	SetConsoleTextAttribute(h, color); // устанавливаем красный цвет для отрисовки "яблока"
	putchar(simbol);
}

int main()
{
	cout << "Choose mode (auto - 'a', manual - 'm') " << endl; 
	char choose = 'm';
	cin >> choose;
	system("cls");
	srand(time(0)); // запуск генератора случайных чисел
	rand(); // холостой ход генератора случаный чисел
	system("mode con cols=51 lines=31"); // установка размеров окна консоли
	MoveWindow(GetConsoleWindow(), 50, 50, 600, 600, true); // установка стартовой позиции окна консоли (50 и 50 - это пиксели
	// относительно верхнего левого угла монитора
	int dx = 1, dy = 0; // создание смещений по осям для движения "змейки"
	COORD apple;
	BrainSneak Brain(width, height);
	do // цикл ставит координаты яблока случанйм образом - но чтобы они не совпадали со "змейкой"
	{
		apple.X = rand() % (width - 2) + 1;
		apple.Y = rand() % (height - 2) + 1;
	} while (Brain.compareCoordApple(apple));

	int sleep_time = 100; // переменная частоты кадров 

	char snake = '*'; // символ для отображения тела "змейки"
	char appleSimbol = 'o'; // символ для отображения "яблока"
	char head = 1; // символ для отображения головы "змейки"

	COORD c; // объект для хранения координат
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // создание хендла потока вывода
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), false }; // создание параметров на отображение курсора
	SetConsoleCursorInfo(h, &cci); //связывание параметров и хендла
	SetConsoleTextAttribute(h, 4); // установка цвета, которым рисуется рамка поля
	for (int y = 0; y < height; y++) // стандартный двойной цикл на отрисовку рамки
	{
		for (int x = 0; x < width; x++)
		{
			char s;
			if (x == 0 && y == 0) // в верхнем левом углу поля - символ соответствующего угла
				s = 218;
			else if (x == 0 && y == height - 1) // нижний левый угол
				s = 192;
			else if (y == 0 && x == width - 1) // верхний правый угол
				s = 191;
			else if (y == height - 1 && x == width - 1) // нижний правый угол
				s = 217;
			else if (y == 0 || y == height - 1) // верхняя и нижняя граница поля
				s = 196;
			else if (x == 0 || x == width - 1) // левая и правая граница поля
				s = 179;
			else s = ' '; // во всех остальных случаях должен быть просто пробел (означает пустую область поля)
			putchar(s); // выводим символ
		}
		cout << endl;
	}
	setObject(h, apple, appleSimbol, 12); //устанавливаем яблоко на его рандомное место
	setObject(h, Brain.getHead(), head, 10); //устанавливаем голову змейки

	bool flag = true; // переменная для управления ходом цикла
	do // собственно цикл игры
	{
		Sleep(sleep_time); // задержка потока программы на заданный ранее интервал

		if (_kbhit() && choose == 'm') // проверяем, была ли нажата какая-либо клавиша и запускаем её обработку в случае ИСТИНЫ
		{
			int k = _getch(); // считываем код клавиши из буфера
			if (k == 0 || k == 224) // если первый код - вспомогательный, считываем второй код
				k = _getch();
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
			case 27: // если была нажата клавиша ESC
				flag = false; // устанавливаем флажок на ЛОЖЬ, чтоб закончить показ движения
				break;
			}
		}
		else
		{
			char k = Brain.decide(apple);
			switch (k) // пропускаем код нажатой клавиши внутрь оператора выбора
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
			case 'n': // tckb ybxtuj nj
				break;
			}
		}

		int X = Brain.arrX.back() + dx; // определяем значение абсциссы головы "змейки" после смещения
		int Y = Brain.arrY.back() + dy; // то же самое для ординаты
		if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) // проверка на достижение границ поля
		{
			flag = false; // пока что - просто установка управляющей переменной цикла 
		}
		else if (X == apple.X && Y == apple.Y) // проверка на достижение "яблока"
		{
			setObject(h, Brain.getHead(), snake, 10);

			Brain.length++; // увеличение длины "змейки" (яблоко проглочено)
			Brain.arrX.push_back(X) ; // установка в массивы позиции нового звена "змейки"
			Brain.arrY.push_back(Y) ; // установка в массивы позиции нового звена "змейки"
			setObject(h, Brain.getHead(), head, 10);

			if (Brain.length == max_length) // проверка, достигла ли длина "змейки" своего максимального значения
			{
				break; // пока что - просто прерываем цикл 
			}

			int i; // переменная для подсчета количества звеньев "змейки", не совпадающих с позицией "яблока"
			do
			{
				apple.X = rand() % (width - 2) + 1; // установка новых координат "яблока"
				apple.Y = rand() % (height - 2) + 1;
				i = 0; // обнуление числа несовпадающих координат
				for (; i < Brain.length; i++) // запуск цикла на сверку совпадений
					if (apple.X == Brain.arrX[i] && apple.Y == Brain.arrY[i]) // если совпадение найдено
						break; // то прерываем цикл for
			} while (i < Brain.length); // поиск новых координат продолжается, пока число несовпадающих координат меньше длины "змейки"
			setObject(h, apple, appleSimbol, 12); //устанавливаем яблоко на его рандомное место
		}
		else // случай, когда голова "змейки" оказалась на новой пустой позиции
		{
			int i = 1; // переменная на количество звеньев, не совпадающих с новой позицией - кроме хвоста "змейки"
			for (; i < Brain.length; i++)
				if (X == Brain.arrX[i] && Y == Brain.arrY[i]) // если совпадение найдено в цикле - прерываемся
					break;
			if (i < Brain.length) // если число несовпадающих звеньев меньше длины "змейки" - то прерываем основной цикл игры
			{
				//break;
			}
			else // а иначе запускаем обработку сдвига "змейки"
			{
				setObject(h, Brain.getTail(), ' '); // Пишем на месте хвоста пробел
				if (Brain.length > 1) // если длина змейки больше 
				{
					setObject(h, Brain.getHead(), snake); // Пишем на месте бывшей головы тело змейки
				}

				for (int i = 0; i < Brain.length - 1; i++) // запускаем цикл свдига координат звеньев "змейки"
				{
					Brain.arrX[i] = Brain.arrX[i + 1]; // обрабатываем все звенья - кроме последнего
					Brain.arrY[i] = Brain.arrY[i + 1];
				}

				Brain.arrX[Brain.length - 1] = X; // устанавливаем новую позицию головы "змейки"
				Brain.arrY[Brain.length - 1] = Y;
				setObject(h, Brain.getHead(), head, 10);
			}
		}
	} while (flag); // выходим из цикла, если сброшена управляющая переменная
	system("cls"); // очищаем экран
	cout << "GAME OVER\n"; // выводим сообщение о конце игры
	system("pause");
}