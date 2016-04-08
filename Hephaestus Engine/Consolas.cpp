#include "Consolas.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;
#pragma once

time_t Current_Time;
ofstream Log_File;
string Date_and_Time;
CONSOLAS Logging_Console;

void CONSOLAS::RefreshConsole()
{
	displayBuffer = loadBuffer;
	SetConsoleActiveScreenBuffer(displayBuffer);
}

void CONSOLAS::Initilize()
{
	loadBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	displayBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(displayBuffer);
	GetConsoleScreenBufferInfo(displayBuffer, &consoleInfo);
	STDZone.name = "STD";
	STDZone.startX = 0;
	STDZone.startY = 0;
	STDZone.endX = consoleInfo.dwSize.X;
	STDZone.endY = consoleInfo.dwSize.Y;
	STDZone.cursorX = 0;
	STDZone.cursorY = 0;
	zones.push_back(STDZone);
}

void CONSOLAS::Print(string In)
{
	if (zones[currentZone].cursorX > zones[currentZone].endX) {
		zones[currentZone].cursorX = zones[currentZone].startX;
		zones[currentZone].cursorY++;
	}
	if (zones[currentZone].cursorY > zones[currentZone].endY) {
		zones[currentZone].cursorX = zones[currentZone].startX;
		zones[currentZone].cursorY = zones[currentZone].startY;
	}
	if (zones[currentZone].cursorX + In.size() > zones[currentZone].endX) {
		int Size = zones[currentZone].endX - zones[currentZone].cursorX - 3;
		string New = "";
		for (int a = 0; a < Size; a++) {
			New = New + In[a];
		}
		New = New + "...";
		In = New;
	}
	COORD Pos = { zones[currentZone].cursorX, zones[currentZone].cursorY };
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(loadBuffer, In.c_str(), In.size(), Pos, &dwBytesWritten);
	zones[currentZone].cursorX = zones[currentZone].cursorX + In.size();
}

void CONSOLAS::SetCursorPosition(int x, int y)
{
	zones[currentZone].cursorX = x;
	zones[currentZone].cursorY = y;
}

void CONSOLAS::CreateZone(string name, int startX, int startY, int endX, int endY)
{
	zone New;
	New.name = name;
	New.startX = startX;
	New.startY = startY;
	New.endX = endX;
	New.endY = endY;
	New.cursorX = startX;
	New.cursorY = startY;
	zones.push_back(New);
}

void CONSOLAS::SetCurrentZone(int zoneIndex)
{
	currentZone = zoneIndex;
}

void CONSOLAS::SearchZone(string name)
{
	for (unsigned a = 0; a < zones.size(); a++) {
		if (zones[a].name == name) {
			SetCurrentZone(a);
		}
	}
}

void CONSOLAS::NewLine()
{
	zones[currentZone].cursorY++;
	zones[currentZone].cursorX = zones[currentZone].startX;
}

void CONSOLAS::Clear()
{
	zones[currentZone].cursorX = zones[currentZone].startX;
	zones[currentZone].cursorY = zones[currentZone].startY;
	int Str_Size = zones[currentZone].endX - zones[currentZone].startX;
	string Blank = "";
	for (int a = 0; a < Str_Size; a++) {
		Blank = Blank + " ";
	}
	for (int a = 0; a < (zones[currentZone].endY - zones[currentZone].startY); a++) {
		Print(Blank);
		NewLine();
	}
	zones[currentZone].cursorX = zones[currentZone].startX;
	zones[currentZone].cursorY = zones[currentZone].startY;
}

void CONSOLAS::PrintZone(string in, string zoneName)
{
	SearchZone(zoneName);
	Print(in);
}

void LOGGING::Initilize(string programName)
{
	Logging_Console.Initilize();
	Logging_Console.CreateZone("Program Tital", 0, 0, 84, 2);
	Logging_Console.CreateZone("Date And Time", 84, 0, 114, 2);
	Logging_Console.CreateZone("FPS", 114, 0, 120, 2);
	Logging_Console.CreateZone("General Log", 0, 2, 84, 30);
	Logging_Console.CreateZone("Error Log", 84, 2, 120, 16);
	Logging_Console.CreateZone("Information Log", 84, 16, 120, 30);
	Current_Time = time(0);
	Date_and_Time = ctime(&Current_Time);
	string Temp = "";
	for (int a = 0; a < Date_and_Time.size() - 1; a++) {
		Temp = Temp + Date_and_Time[a];
	}
	Date_and_Time = Temp;
	string File = "Log Data.log";
	Log_File.open(File.c_str());
	if (Log_File.is_open()) {
		Log(1, "Created New Log File", "Logging/Initilize");
		Log(6, Date_and_Time, "Logging/Initilize");
	}
	Logging_Console.PrintZone(programName, "Program Tital");
}

void LOGGING::Log(int type, string log, string location)
{
	string Line, Log_Type, logLocation;
	if (type == 1) {
		Log_Type = "Success";
	}
	if (type == 2) {
		Log_Type = "Warning";
	}
	if (type == 3) {
		Log_Type = "Error";
	}
	if (type == 4) {
		Log_Type = "Critical Error";
	}
	if (type == 5) {
		Log_Type = "Info";
	}
	if (type == 6) {
		Log_Type = "Date/Time";
	}
	if (type > 0) {
		Line = "[" + Log_Type + "]" + log + "[" + location + "]";
		logLocation = log + "[" + location + "]";
		Logging_Console.PrintZone(Line, "General Log");
		Logging_Console.NewLine();
	}
	Log_File << Line << "\n";
	if (type == 5) {
		Logging_Console.PrintZone(logLocation, "Information Log");
		Logging_Console.NewLine();
	}
	if (type == 3 || type == 4) {
		Logging_Console.PrintZone(logLocation, "Error Log");
		Logging_Console.NewLine();
	}
	if (type == 0) {
		Logging_Console.PrintZone(log, "FPS");
	}
	Current_Time = time(0);
	Date_and_Time = ctime(&Current_Time);
	string Temp = "";
	for (int a = 0; a < Date_and_Time.size() - 1; a++) {
		Temp = Temp + Date_and_Time[a];
	}
	Date_and_Time = Temp;
	Logging_Console.SearchZone("Date And Time");
	Logging_Console.Clear();
	Logging_Console.Print(Date_and_Time);
	Logging_Console.RefreshConsole();
}

void LOGGING::LogFPS(float FPS)
{
	string str_FPS = to_string(FPS);
	string Temp;
	for (int a = 0; a < 6; a++) {
		Temp = Temp + str_FPS[a];
	}
	str_FPS = Temp;
	Logging_Console.SearchZone("FPS");
	Logging_Console.Clear();
	Logging_Console.Print(str_FPS);
	Current_Time = time(0);
	Date_and_Time = ctime(&Current_Time);
	Temp = "";
	for (int a = 0; a < Date_and_Time.size() - 1; a++) {
		Temp = Temp + Date_and_Time[a];
	}
	Date_and_Time = Temp;
	Logging_Console.SearchZone("Date And Time");
	Logging_Console.Clear();
	Logging_Console.Print(Date_and_Time);
	Logging_Console.RefreshConsole();
}

void LOGGING::Terminate()
{
	Log(1, "Terminated Log", "Logging/Terminate");
	Log_File.close();
}
