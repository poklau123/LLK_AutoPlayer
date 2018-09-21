#pragma once
#include "Point.h"

class Game
{
private:
	int width;
	int height;
public:
	Point** matrix;

	Game(int _width, int _height);

	bool init(int* arr);

	int getPointType(int x, int y);

	bool isTwoPointDirectlyLinkable(Point* a, Point* b);

	Point* getNeighborEmptyPoint(Point* point);

	bool isTwoPointLinkable(Point* a, Point* b);

	Point* getPoint(int x, int y);

	void linkTwoPoint(Point* a, Point* b);

	void printMatrix();

	~Game();
};

