#include "pch.h"
#include "AI.h"

AI::AI(Game* game)
{
	this->game = game;

	for (int y = 1; y < game->height - 1; y++)
	{
		for (int x = 1; x < game->width - 1; x++)
		{
			Point* point = game->getPoint(x, y);
			int type = point->getType();

			this->classify[type].push_back(*point);
		}
	}
}

vector<Point> AI::play()
{
	vector<Point> points;
	while (this->classify.size() > 0)
	{
		bool flag = false;		//当前是否有解
		for (map<int, vector<Point>>::iterator classify_it = this->classify.begin(); classify_it != this->classify.end();)
		{
			vector<Point>* group = &(classify_it->second);

			for (int i = 0; group->size() > 0 && (i < group->size() - 1); i++) 
			{
				for (int j = i + 1; j < group->size(); j++)
				{
					if (game->linkTwoPoint(&group->at(i), &group->at(j)))
					{
						game->printMatrix();

						points.push_back(group->at(i));
						points.push_back(group->at(j));

						group->erase(group->begin() + j);
						group->erase(group->begin() + i);

						flag = true;
					}
				}
			}
			if (group->size() == 0)
			{
				classify_it = this->classify.erase(classify_it);
			}
			else {
				classify_it++;
			}
		}
		if (!flag)
		{
			return vector<Point>();
		}
	}
	return points;
}

vector<Point> AI::calc()
{
	vector<Point> points = this->play();
	while (points.size() == 0)
	{
		for (int i = 0; i < this->classify.size(); i++)
		{
			std::random_shuffle(this->classify.find(i)->second.begin(), this->classify.find(i)->second.end());
		}
		points = this->play();
	}
	return points;
}

AI::~AI()
{
}
