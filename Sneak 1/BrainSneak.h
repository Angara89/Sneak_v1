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
	int dx;
	int dy;
	std::vector<int> arrX;
	std::vector<int> arrY;
	int length;
	void decide(COORD apple);
	bool compareCoordApple(COORD apple);
	COORD getHead();
	BrainSneak(int widthWall, int heightWall);
	COORD getTail();
	class BrainSneakEx{};
};

