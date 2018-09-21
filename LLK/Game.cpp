#include "pch.h"
#include "Game.h"

Game::Game()
{
}

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

bool Game::init(vector<int> arr)
{
	if (arr.size() != (this->width - 2) * (this->height - 2)) {
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

	return true;
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
	if (a->y == b->y)
	{
		int _y = a->y;
		int _x_begin, _x_end;
		a->x < b->x ? (_x_begin = a->x, _x_end = b->x) : (_x_begin = b->x, _x_end = a->x);

		if (_x_begin + 1 == _x_end) return true;
		for (int _x = _x_begin + 1; _x < _x_end; _x++)
		{
			if (this->getPointType(_x, _y) != EMPTY_POINT) {
				return false;
			}
		}
		return true;
	}
	if (a->x == b->x)
	{
		int _x = a->x;
		int _y_begin, _y_end;
		a->y < b->y ? (_y_begin = a->y, _y_end = b->y) : (_y_begin = b->y, _y_end = a->y);

		if (_y_begin + 1 == _y_end) return true;
		for (int _y = _y_begin + 1; _y < _y_end; _y++)
		{
			if (this->getPointType(_x, _y) != EMPTY_POINT) {
				return false;
			}
		}
		return true;
	}
	
	return false;
}

vector<Point> Game::getNeighborEmptyPoint(Point* point)
{
	vector<Point> points;

	int x = point->x;
	int y = point->y;

	for (int i = x - 1; i >= 0; i--)
	{
		if (this->getPointType(i, y) != EMPTY_POINT) break;
		points.push_back(this->matrix[y][i]);
	}
	for (int i = x + 1; i < this->width; i++)
	{
		if (this->getPointType(i, y) != EMPTY_POINT) break;
		points.push_back(this->matrix[y][i]);
	}
	for (int j = y - 1; j >= 0; j--)
	{
		if (this->getPointType(x, j) != EMPTY_POINT) break;
		points.push_back(this->matrix[j][x]);
	}
	for (int j = y + 1; j < this->height; j++)
	{
		if (this->getPointType(x, j) != EMPTY_POINT) break;
		points.push_back(this->matrix[j][x]);
	}

	return points;
}

bool Game::isTwoPointLinkable(Point * a, Point * b)
{
	if (this->isTwoPointDirectlyLinkable(a, b)) {
		return true;
	}


	vector<Point> a_neighbor = this->getNeighborEmptyPoint(a);
	vector<Point> b_neighbor = this->getNeighborEmptyPoint(b);
	for (vector<Point>::iterator a_it = a_neighbor.begin(); a_it != a_neighbor.end(); a_it++)
	{
		if (this->isTwoPointDirectlyLinkable(&*a_it, b)) return true;
	}
	for (vector<Point>::iterator b_it = b_neighbor.begin(); b_it != b_neighbor.end(); b_it++)
	{
		if (this->isTwoPointDirectlyLinkable(&*b_it, a)) return true;
	}

	for (vector<Point>::iterator a_it = a_neighbor.begin(); a_it != a_neighbor.end(); a_it++)
	{
		for (vector<Point>::iterator b_it = b_neighbor.begin(); b_it != b_neighbor.end(); b_it++)
		{
			if (this->isTwoPointDirectlyLinkable(&*a_it, &*b_it)) return true;
		}
	}

	return false;
}

Point* Game::getPoint(int x, int y)
{
	return &(this->matrix[y][x]);
}

bool Game::linkTwoPoint(Point * a, Point * b)
{
	if (a->getType() != b->getType()) {
		return false;
	}
	if (a->getType() == EMPTY_POINT || b->getType() == EMPTY_POINT) {
		return false;
	}
	if (this->isTwoPointLinkable(a, b))
	{
		this->getPoint(a->x, a->y)->setType(EMPTY_POINT);
		this->getPoint(b->x, b->y)->setType(EMPTY_POINT);
		return true;
	}
	return false;
}

void Game::printMatrix()
{
	cout << endl;
	for (int y = 0; y < this->height; y++)
	{
		for (int x = 0; x < this->width; x++)
		{
			int type = this->getPoint(x, y)->getType();
			if (type == EMPTY_POINT)
			{
				cout << "- ";
			}
			else {
				cout << type << ' ';
			}			
		}
		cout << endl;
	}
}


Game::~Game()
{
	for (int y = 0; y < this->height; y++)
	{
		delete[] this->matrix[y];
	}
}
