#include "pch.h"
#include "Point.h"


Point::Point()
{
}

Point::Point(int x, int y, int type = EMPTY_POINT)
{
	this->x = x;
	this->y = y;
	this->type = type;
}

bool Point::isEmpty()
{
	return this->type == EMPTY_POINT;
}

void Point::setCoordinate(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Point::setType(int type = EMPTY_POINT)
{
	this->type = type;
}

int Point::getType()
{
	return this->type;
}


Point::~Point()
{
}
