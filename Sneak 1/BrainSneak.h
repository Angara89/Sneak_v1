#pragma once 
#include <Windows.h>
#include <vector>

const int max_length = 500;
class BrainSneak
{
private:
	int widthWall;
	int heightWall;


public:
	std::vector<int> arrX;
	std::vector<int> arrY;
	int length;
	char decide(COORD apple);
	bool compareCoordApple(COORD apple);
	COORD getHead();
	BrainSneak(int widthWall, int heightWall);
	COORD getTail();
};

