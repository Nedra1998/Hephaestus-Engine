#include "stdlibraries.h"
#include "Classes.h"
using namespace std;

INITIALIZE coreInitialize;
WINDOW coreWindow;

int main(int argc, char** argv)
{
	coreInitialize.InitializeLogging("Hephaestus Engine V-00.00.00");
	coreInitialize.GLUTInitialize(argc, argv);
	coreWindow.GenorateWindow("Hephaestus Engine V-00.00.00", 500, 500);
	coreWindow.DestroyCurrentWindow();
}