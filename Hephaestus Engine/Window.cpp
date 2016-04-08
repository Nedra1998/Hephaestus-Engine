#include "stdlibraries.h"
#include "Classes.h"
using namespace std;

INITIALIZE windowInitialize;


void WINDOW::GenorateWindow(string programName, int width, int height)
{
	unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;
	displayMode = windowInitialize.Defaults(displayMode, width, height);
	glutInitDisplayMode(displayMode);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(300, 200);
	mainWindow = glutCreateWindow(programName.c_str());
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	LOGGING::Log(1, "Created: " + programName + " window", "Window.cpp/GenorateWindow");
	LOGGING::Log(5, "Window size: " + to_string(width) + "x" + to_string(height), "Window.cpp/GenorateWindow");
}

void WINDOW::LoadWindowSettings()
{
}

void WINDOW::DestroyCurrentWindow()
{
	glutDestroyWindow(mainWindow);
	LOGGING::Log(1, "Destroyed current window", "Window.cpp/DestoryCurrentWindow");
}
