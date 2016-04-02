#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
using namespace std;

class Consolas {
private:
	struct Zone {
		string Name;
		int Start_X, Start_Y, End_X, End_Y;
		int Cursor_X, Cursor_Y;
	};
	Zone STD_Zone;
	HANDLE Load_Buffer, Display_Buffer;
	_CONSOLE_SCREEN_BUFFER_INFO Console_Info;

	int Current_Zone = 0;

	vector<Zone> Zones;
	int Background_Color_Int, Text_Color_Int;

public:
	/*Basic Functions*/
	void Refresh_Console();
	void Initilize();
	void Print(string In);
	void Set_Cursor_Position(int x, int y);
	void Create_Zone(string Name, int Start_X, int Start_Y, int End_X, int End_Y);
	void Set_Current_Zone(int Zone_Index);
	void Search_Zone(string Name);
	void New_Line();
	void Clear();
	/*Advanced Functions*/
	void Print_Zone(string In, string Zone_Name);
};

namespace Logging {
	void Initilize(string Program_Name);
	void Log(int Type, string Log, string Location);
	void Log_FPS(float FPS);
	void Terminate();
};