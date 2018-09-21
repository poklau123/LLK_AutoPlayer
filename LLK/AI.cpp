#include "pch.h"
#include "AI.h"

AI::AI(Game* game)
{
	this->game = game;

	for (int y = 1; y < game->height - 1; y++)
	{
		for (int x = 1; x < game->width - 1; x++)
		{
			Point point = game->getPoint(x, y);
			int type = point.getType();

			this->classify[type].push_back(point);
		}
	}
}

vector<Point> AI::play()
{
	vector<Point> points;
	while (this->classify.size() > 0)
	{
		for (map<int, vector<Point>>::iterator classify_it = this->classify.begin(); classify_it != this->classify.end(); classify_it++)
		{
			vector<Point>* group = &classify_it->second;
			for (vector<Point>::iterator it_a = group->begin(); it_a != group->end() - 1; it_a++)
			{
				int flag = false;
				for (vector<Point>::iterator it_b = it_a + 1; it_b != group->end();) {
					if (game->linkTwoPoint(&*it_a, &*it_b))
					{
						game->printMatrix();

						points.push_back(*it_a);
						points.push_back(*it_b);

						group->erase(it_b);
						group->erase(it_a);


						flag = true;
						break;

					}
					else {
						it_b++;
					}
				}
				if (flag) {
					break;
				}
			}
			if (group->size() == 0)
			{
				classify_it = this->classify.erase(classify_it);
			}
		}
	}
	return points;
}

AI::~AI()
{
}
