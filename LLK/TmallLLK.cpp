#include "pch.h"
#include "TmallLLK.h"
#define MAX_PATH 1000

void TmailLLK::tap(int x, int y)
{
	float x_offset = this->start_x + this->step_x * (x - 0.5);
	float y_offset = this->start_y + this->step_y * (y - 0.5);

	CString str;
	str.Format(L"adb shell input tap %d %d", (int)x_offset, (int)y_offset);
	LPWSTR cmd = (LPWSTR)(LPCTSTR)str;
	CreateProcess(NULL, cmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &this->si, &this->pi);
	WaitForSingleObject(this->pi.hProcess, 100);
}

CString TmailLLK::screenshot(const char* filename)
{

	char path[MAX_PATH];
	_getcwd(path, MAX_PATH);
	CString _path(path);

	CString _filename(filename);

	CString str_cap, str_pull, str_rm, str_fn;
	str_fn.Format(L"%s\\%s", _path, _filename);
	str_cap.Format(L"adb shell screencap -p /sdcard/%s", _filename);
	str_pull.Format(L"adb pull /sdcard/%s %s", _filename, str_fn);
	str_rm.Format(L"adb shell rm /sdcard/%s", _filename);

	LPWSTR cmd_cap = (LPWSTR)(LPCTSTR)str_cap;
	LPWSTR cmd_pull = (LPWSTR)(LPCTSTR)str_pull;
	LPWSTR cmd_rm = (LPWSTR)(LPCTSTR)str_rm;

	char fn[MAX_PATH] = "\0";
	sprintf_s(fn, "%s\\%s", path, filename);
	if (remove(fn))
	{
		cout << "delete file failed" << fn << endl;
	}

	DWORD dwRetun = 0;
	CreateProcess(NULL, cmd_cap, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &this->si, &this->pi);
	WaitForSingleObject(this->pi.hProcess, INFINITE);
	CreateProcess(NULL, cmd_pull, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &this->si, &this->pi);
	WaitForSingleObject(this->pi.hProcess, INFINITE);
	CreateProcess(NULL, cmd_rm, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &this->si, &this->pi);
	WaitForSingleObject(this->pi.hProcess, INFINITE);

	return str_fn;
}


TmailLLK::TmailLLK()
{
}

TmailLLK::TmailLLK(int device_width, int device_height, int row, int col)
{
	this->device_width = device_width;
	this->device_height = device_height;

	this->row = row;
	this->col = col;

	this->start_x = (float)0;
	this->start_y = (float)500;
	this->step_x = (float)device_width / col;
	this->step_y = step_x;

	ZeroMemory(&this->si, sizeof(this->si));
	this->si.cb = sizeof(this->si);
	ZeroMemory(&this->pi, sizeof(this->pi));
}

TmailLLK::~TmailLLK()
{
}
