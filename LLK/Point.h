#pragma once

#define EMPTY_POINT -1

class Point
{
private:
	int type;
public:
	int x;
	int y;

	Point();

	Point(int x, int y, int type);

	bool isEmpty();

	void setCoordinate(int x, int y);

	void setType(int type);

	int getType();

	~Point();
};

