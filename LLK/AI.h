#pragma once
#include "Game.h"
#include <map>

class AI
{
public:
	Game* game;
	map<int, vector<Point>> classify;

	AI(Game* game);

	vector<Point> play();

	~AI();
};

