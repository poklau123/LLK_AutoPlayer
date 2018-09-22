#pragma once
#include <iostream>
#include <Windows.h>
#include <atlstr.h>
#include <direct.h>
#include <stdio.h>
using namespace std;

class TmailLLK
{
public:
	int device_width;
	int device_height;

	float start_x;
	float start_y;
	float step_x;
	float step_y;

	int row;
	int col;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	void tap(int x, int y);
	CString screenshot(const char* filename);

	TmailLLK();
	TmailLLK(int device_width, int device_height, int row, int col);
	~TmailLLK();
};

