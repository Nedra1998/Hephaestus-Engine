#pragma once
#include "stdlibraries.h"
#include "Definitons.h"
using namespace std;

class WINDOW
{
private:
	
	int mainWindow;
	bool window = false;
	WindowSettings windowSettings;

public:
	void GenorateWindow(string programName, int width, int height);
	WindowSettings LoadWindowSettings();
	void GenorateFromSettings();
	void DestroyCurrentWindow();
};