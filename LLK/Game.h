#pragma once
#include "Point.h"
#include <vector>
#include <iostream>
using namespace std;

class Game
{
public:
	Point** matrix;
	int width;
	int height;

	Game();
	Game(int _width, int _height);

	bool init(vector<int> arr);

	int getPointType(int x, int y);

	bool isTwoPointDirectlyLinkable(Point* a, Point* b);

	vector<Point> getNeighborEmptyPoint(Point* point);

	bool isTwoPointLinkable(Point* a, Point* b);

	Point* getPoint(int x, int y);

	bool linkTwoPoint(Point* a, Point* b);

	void printMatrix();

	~Game();
};

