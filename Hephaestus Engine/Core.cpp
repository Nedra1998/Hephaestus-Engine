#include "stdlibraries.h"
#include "Classes.h"
using namespace std;

INITIALIZE coreInitialize;
WINDOW coreWindow;

int main(int argc, char** argv)
{
	coreInitialize.InitializeLogging("Hephaestus Engine V-00.00.06");
	coreInitialize.GLUTInitialize(argc, argv);
	coreWindow.GenorateFromSettings();
	coreInitialize.InitializeGl3W();
	while (1);
	coreWindow.DestroyCurrentWindow();
}