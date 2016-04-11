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
		string rawFile;
		vector<Variable> variables;
	};
	struct VariablePointer
	{
		int variablePointer, scriptPointer;
		string name;
	};
	vector<ScriptFile> scripts;
	vector<VariablePointer> variables;

	void CreateVariable(string name);
	void SetVariableValueInt(int value);
	void SetVariableValueChar(char value);
	void SetVariableValueFloat(float value);
	void SetVariableValueBool(bool value);
	void SetVariableValueString(string value);

	void LoadScript(string rawFile);
public:
	void LoadHRSFile(string fileDirectory, string vectorSaveName);
	string DetermineStringValue(string valueName);
	bool DetermineBoolValue(string valueName);
	void ClearHRSVector();
};