#pragma once
#include "stdlibraries.h"
using namespace std;

class INTERPRETER
{
private:
	struct Variable
	{
		string variableName;
		string stringValue;
		int intValue;
		char charValue;
		float floatValue;
		bool boolValue;
	};
	struct ScriptFile
	{
		vector<string> rawFile;
		vector<Variable> variables;
	};
	vector<ScriptFile> scripts;
public:
	void LoadHRSFile(string fileDirectory, string vectorSaveName);
	string DetermineStringValue(string valueName);
	bool DetermineBoolValue(string valueName);
	void ClearHRSVector();
};