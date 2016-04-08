#pragma once
#include "stdlibraries.h"
using namespace std;

class WINDOW
{
private:
	int mainWindow;
	bool window = false;
public:
	void GenorateWindow(string programName, int width, int height);
	void LoadWindowSettings();
	void DestroyCurrentWindow();
};