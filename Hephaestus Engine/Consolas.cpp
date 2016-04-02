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
Consolas Logging_Console;

void Consolas::Refresh_Console()
{
	Display_Buffer = Load_Buffer;
	SetConsoleActiveScreenBuffer(Display_Buffer);
}

void Consolas::Initilize()
{
	Load_Buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	Display_Buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(Display_Buffer);
	GetConsoleScreenBufferInfo(Display_Buffer, &Console_Info);
	STD_Zone.Name = "STD";
	STD_Zone.Start_X = 0;
	STD_Zone.Start_Y = 0;
	STD_Zone.End_X = Console_Info.dwSize.X;
	STD_Zone.End_Y = Console_Info.dwSize.Y;
	STD_Zone.Cursor_X = 0;
	STD_Zone.Cursor_Y = 0;
	Zones.push_back(STD_Zone);
}

void Consolas::Print(string In)
{
	if (Zones[Current_Zone].Cursor_X > Zones[Current_Zone].End_X) {
		Zones[Current_Zone].Cursor_X = Zones[Current_Zone].Start_X;
		Zones[Current_Zone].Cursor_Y++;
	}
	if (Zones[Current_Zone].Cursor_Y > Zones[Current_Zone].End_Y) {
		Zones[Current_Zone].Cursor_X = Zones[Current_Zone].Start_X;
		Zones[Current_Zone].Cursor_Y = Zones[Current_Zone].Start_Y;
	}
	if (Zones[Current_Zone].Cursor_X + In.size() > Zones[Current_Zone].End_X) {
		int Size = Zones[Current_Zone].End_X - Zones[Current_Zone].Cursor_X - 3;
		string New = "";
		for (int a = 0; a < Size; a++) {
			New = New + In[a];
		}
		New = New + "...";
		In = New;
	}
	COORD Pos = { Zones[Current_Zone].Cursor_X, Zones[Current_Zone].Cursor_Y };
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(Load_Buffer, In.c_str(), In.size(), Pos, &dwBytesWritten);
	Zones[Current_Zone].Cursor_X = Zones[Current_Zone].Cursor_X + In.size();
}

void Consolas::Set_Cursor_Position(int x, int y)
{
	Zones[Current_Zone].Cursor_X = x;
	Zones[Current_Zone].Cursor_Y = y;
}

void Consolas::Create_Zone(string Name, int Start_X, int Start_Y, int End_X, int End_Y)
{
	Zone New;
	New.Name = Name;
	New.Start_X = Start_X;
	New.Start_Y = Start_Y;
	New.End_X = End_X;
	New.End_Y = End_Y;
	New.Cursor_X = Start_X;
	New.Cursor_Y = Start_Y;
	Zones.push_back(New);
}

void Consolas::Set_Current_Zone(int Zone_Index)
{
	Current_Zone = Zone_Index;
}

void Consolas::Search_Zone(string Name)
{
	for (unsigned a = 0; a < Zones.size(); a++) {
		if (Zones[a].Name == Name) {
			Set_Current_Zone(a);
		}
	}
}

void Consolas::New_Line()
{
	Zones[Current_Zone].Cursor_Y++;
	Zones[Current_Zone].Cursor_X = Zones[Current_Zone].Start_X;
}

void Consolas::Clear()
{
	Zones[Current_Zone].Cursor_X = Zones[Current_Zone].Start_X;
	Zones[Current_Zone].Cursor_Y = Zones[Current_Zone].Start_Y;
	int Str_Size = Zones[Current_Zone].End_X - Zones[Current_Zone].Start_X;
	string Blank = "";
	for (int a = 0; a < Str_Size; a++) {
		Blank = Blank + " ";
	}
	for (int a = 0; a < (Zones[Current_Zone].End_Y - Zones[Current_Zone].Start_Y); a++) {
		Print(Blank);
		New_Line();
	}
	Zones[Current_Zone].Cursor_X = Zones[Current_Zone].Start_X;
	Zones[Current_Zone].Cursor_Y = Zones[Current_Zone].Start_Y;
}

void Consolas::Print_Zone(string In, string Zone_Name)
{
	Search_Zone(Zone_Name);
	Print(In);
}

void Logging::Initilize(string Program_Name)
{
	Logging_Console.Initilize();
	Logging_Console.Create_Zone("Program Tital", 0, 0, 84, 2);
	Logging_Console.Create_Zone("Date And Time", 84, 0, 114, 2);
	Logging_Console.Create_Zone("FPS", 114, 0, 120, 2);
	Logging_Console.Create_Zone("General Log", 0, 2, 84, 30);
	Logging_Console.Create_Zone("Error Log", 84, 2, 120, 16);
	Logging_Console.Create_Zone("Information Log", 84, 16, 120, 30);
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
	Logging_Console.Print_Zone(Program_Name, "Program tital");
}

void Logging::Log(int Type, string Log, string Location)
{
	string Line, Log_Type;
	if (Type == 1) {
		Log_Type = "Success";
	}
	if (Type == 2) {
		Log_Type = "Warning";
	}
	if (Type == 3) {
		Log_Type = "Error";
	}
	if (Type == 4) {
		Log_Type = "Critical Error";
	}
	if (Type == 5) {
		Log_Type = "Info";
	}
	if (Type == 6) {
		Log_Type = "Date/Time";
	}
	if (Type > 0) {
		Line = "[" + Log_Type + "]>>" + Log + "<<[" + Location + "]";
		Logging_Console.Print_Zone(Line, "General Log");
		Logging_Console.New_Line();
	}
	Log_File << Line << "\n";
	if (Type == 5) {
		Logging_Console.Print_Zone(Line, "Information Log");
		Logging_Console.New_Line();
	}
	if (Type == 3 || Type == 4) {
		Logging_Console.Print_Zone(Line, "Error Log");
		Logging_Console.New_Line();
	}
	if (Type == 0) {
		Logging_Console.Print_Zone(Log, "FPS");
	}
	Current_Time = time(0);
	Date_and_Time = ctime(&Current_Time);
	string Temp = "";
	for (int a = 0; a < Date_and_Time.size() - 1; a++) {
		Temp = Temp + Date_and_Time[a];
	}
	Date_and_Time = Temp;
	Logging_Console.Search_Zone("Date And Time");
	Logging_Console.Clear();
	Logging_Console.Print(Date_and_Time);
	Logging_Console.Refresh_Console();
}

void Logging::Log_FPS(float FPS)
{
	string str_FPS = to_string(FPS);
	string Temp;
	for (int a = 0; a < 6; a++) {
		Temp = Temp + str_FPS[a];
	}
	str_FPS = Temp;
	Logging_Console.Search_Zone("FPS");
	Logging_Console.Clear();
	Logging_Console.Print(str_FPS);
	Current_Time = time(0);
	Date_and_Time = ctime(&Current_Time);
	Temp = "";
	for (int a = 0; a < Date_and_Time.size() - 1; a++) {
		Temp = Temp + Date_and_Time[a];
	}
	Date_and_Time = Temp;
	Logging_Console.Search_Zone("Date And Time");
	Logging_Console.Clear();
	Logging_Console.Print(Date_and_Time);
	Logging_Console.Refresh_Console();
}

void Logging::Terminate()
{
	Log(1, "Terminated Log", "Logging/Terminate");
	Log_File.close();
}
