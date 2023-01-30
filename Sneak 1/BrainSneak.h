#pragma once 
#include <Windows.h>
#include <vector>
#include <queue>
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
	std::queue<int> path;


	void decide(COORD apple);
	void decide2(COORD apple);
	void usersDecide(int k);
	bool compareCoordApple(COORD apple);
	COORD getHead();
	BrainSneak(int widthWall, int heightWall);
	COORD getTail();
	class BrainSneakEx{};
};

