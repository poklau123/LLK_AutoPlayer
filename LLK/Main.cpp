// LLK.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Game.h"
#include "AI.h"
#include "Windows.h"
#include "TmallLLK.h"
#include "ImgProc.h"


int main()
{

	TmailLLK* llk = new TmailLLK(1080, 2160, 10, 7);
	CString file = llk->screenshot("test.png");

	ImgProc* imgProc = new ImgProc(file);
	imgProc->CropMainArea(llk);
	imgProc->CropSliceAll();

	vector<int> series = imgProc->getSeries();

	Game* game = new Game(7, 10);
	game->init(series);

	game->printMatrix();

	AI* ai = new AI(game);
	vector<Point> steps = ai->calc();
	
	int i = 0;
	for (vector<Point>::iterator it = steps.begin(); it != steps.end(); it++)
	{
		cout << "Point Click.(" << it->x << ", " << it->y << ')' << endl;

		llk->tap(it->x, it->y);
	}
}
