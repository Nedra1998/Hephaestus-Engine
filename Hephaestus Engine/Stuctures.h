#include "stdlibraries.h"
using namespace std;

struct Version
{
	int majorVersion, minorVersion, subVersion;
};
struct IntPair
{
	int a, b;
};
struct WindowSettings
{
	string programName;
	Version versionNumber;
	int ratio, resolution;
	IntPair ratioInts;
	IntPair resolutionInts;
	bool fullscreen;
};