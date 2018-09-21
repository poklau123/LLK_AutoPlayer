#include "pch.h"
#include "Game.h"


Game::Game(int _width, int _height)
{
	this->width = _width + 2;
	this->height = _height + 2;

	this->matrix = new Point* [this->height];
	for (int y = 0; y < this->height; y++)
	{
		this->matrix[y] = new Point[this->width];
		for (int x = 0; x < this->width; x++)
		{
			this->matrix[y][x].setCoordinate(x, y);
		}
	}
}

bool Game::init(int * arr)
{
	if (sizeof(arr) != (this->width - 2) * (this->height - 2)) {
		return false;
	}
	int pos = 0;
	for (int y = 1; y < this->height - 1; y++)
	{
		for (int x = 1; x < this->width - 1; x++)
		{
			this->matrix[y][x].setType(arr[pos++]);
		}
	}
}

int Game::getPointType(int x, int y)
{
	return this->matrix[y][x].getType();
}

bool Game::isTwoPointDirectlyLinkable(Point* a, Point* b)
{
	if (a->x != b->x && a->y != b->y)
	{
		return false;
	}
	if (a->y = b->y)
	{
		int _y = a->y;
		int _x_begin, _x_end;
		a->x < b->x ? (_x_begin = a->x, _x_end = b->x) : (_x_begin = b->x, _x_end = a->x);

		if (_x_begin + 1 == _x_end) return true;
		for (int _x = _x_begin + 1; _x < _x_end; _x++)
		{
			if (this->getPoint(_x, _y) != EMPTY_POINT) {
				return false;
			}
		}
		return true;
	}
	if (a->x = b->x)
	{
		int _x = a->x;
		int _y_begin, _y_end;
		a->y < b->y ? (_y_begin = a->y, _y_end = b->y) : (_y_begin = b->y, _y_end = a->y);

		if (_y_begin + 1 == _y_end) return true;
		for (int _y = _y_begin + 1; _x < _y_end; _y++)
		{
			if (this->getPoint(_x, _y) != EMPTY_POINT) {
				return false;
			}
		}
		return true;
	}
}

Point * Game::getNeighborEmptyPoint(Point* point)
{
	Point* points;

	int x = point->x;
	int y = point->y;

	for (int i = x - 1; i >= 0; i--)
	{
		if (this->getPointType(i, y) != EMPTY_POINT) break;
	}
}


Game::~Game()
{
}
