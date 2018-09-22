#pragma once
#include "Game.h"
#include <map>
#include <algorithm>

class AI
{
public:
	Game* game;
	map<int, vector<Point>> classify;

	AI(Game* game);

	vector<Point> play();

	vector<Point> calc();

	~AI();
};

