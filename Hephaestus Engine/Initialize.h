#pragma once
#include "stdlibraries.h"
using namespace std;

class INITIALIZE
{
private:
public:
	void InitializeLogging(string programName);
	void GLUTInitialize(int argc, char**argv);
	void GLVersion();

	unsigned int Defaults(unsigned int displayMode, int &width, int &height);

	void FullInitilization(string settingsDirectory);
};