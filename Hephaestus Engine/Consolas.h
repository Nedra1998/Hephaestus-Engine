#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
using namespace std;

class CONSOLAS
{
private:
	struct zone {
		string name;
		int startX, startY, endX, endY;
		int cursorX, cursorY;
	};
	zone STDZone;
	HANDLE loadBuffer, displayBuffer;
	_CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

	int currentZone = 0;

	vector<zone> zones;
	int backgroundColorInt, textColorInt;

public:
	/*Basic Functions*/
	void RefreshConsole();
	void Initilize();
	void Print(string in);
	void SetCursorPosition(int x, int y);
	void CreateZone(string name, int startX, int startY, int endX, int endY);
	void SetCurrentZone(int zoneIndex);
	void SearchZone(string name);
	void NewLine();
	void Clear();
	/*Advanced Functions*/
	void PrintZone(string in, string zoneName);
};

namespace LOGGING
{
	void Initilize(string programName);
	void Log(int type, string log, string location);
	void LogFPS(float FPS);
	void Terminate();
};