#pragma once
#include "stdlibraries.h"
using namespace std;

class WINDOW
{
private:
	struct DisplayRatio
	{
		int width, height;
	};
	struct DisplayResolution
	{
		int width, height;
	};
	
	int mainWindow;
	bool window = false;
	string windowName;
	DisplayRatio windowDisplayRatio;
	DisplayResolution windowDisplayResolution;

public:
	void GenorateWindow(string programName, int width, int height);
	void LoadWindowSettings();
	void DestroyCurrentWindow();
};