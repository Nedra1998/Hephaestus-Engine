#include "stdlibraries.h"
#include "Classes.h"
using namespace std;

INITIALIZE coreInitialize;
WINDOW coreWindow;

int main(int argc, char** argv)
{
	coreInitialize.InitializeLogging("Hephaestus Engine V-00.00.05");
	coreInitialize.GLUTInitialize(argc, argv);
	coreWindow.GenorateFromSettings();
	while (1);
	coreWindow.DestroyCurrentWindow();
}