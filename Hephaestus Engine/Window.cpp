#include "stdlibraries.h"
#include "Classes.h"
using namespace std;

INITIALIZE windowInitialize;

void WINDOW::GenorateWindow(string programName, int width, int height)
{
	unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL | GLUT_FULL_SCREEN;
	displayMode = windowInitialize.Defaults(displayMode, width, height);
	glutInitDisplayMode(displayMode);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(300, 200);
	mainWindow = glutCreateWindow(programName.c_str());
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	LOGGING::Log(1, "Genorated: " + programName, "Window.cpp/GenorateWindow");
}

WindowSettings WINDOW::LoadWindowSettings()
{
	WindowSettings windowInit;
	string full;
	ifstream loadSettings("Hephaestus Support Files/WindowSettings.supt");
	if (loadSettings.is_open()) {
		LOGGING::Log(1, "Loaded WindowSettings.supt", "Window.cpp/LoadWindowSettings");
		getline(loadSettings, windowInit.programName);
		loadSettings >> windowInit.versionNumber.majorVersion >> windowInit.versionNumber.minorVersion >> windowInit.versionNumber.subVersion;
		loadSettings >> windowInit.ratio >> windowInit.resolution;
		getline(loadSettings, full);
		if (full == "false") {
			windowInit.fullscreen = false;
		}
		else if (full == "true") {
			windowInit.fullscreen = true;
		}
		loadSettings.close();
	}
	else {
		LOGGING::Log(3, "Unable To Load WindowSettings.supt", "Window.cpp/LoadWindowSettings");
	}
	int ra = 0, re = 0;
	string ratio, resolution, tempStr;
	ifstream loadResolution("Hephaestus Support Files/Resolutions.supt");
	if (loadResolution.is_open()) {
		LOGGING::Log(1, "Loaded Resolutions.supt", "Winodw.cpp/LoadWindowSettings");
		while (getline(loadResolution, tempStr)) {
			re++;
			if (tempStr[0] == '[') {
				re = 0;
				ra++;
				if (ra == windowInit.ratio) {
					ratio = tempStr;
				}
			}
			if (re == windowInit.resolution && ra == windowInit.ratio) {
				resolution = tempStr;
			}
		}
		loadResolution.close();
	}
	else {
		LOGGING::Log(3, "Unable To Load Resolutions.supt", "Window.cpp/LoadWindowSettings");
	}
	string tempInt;
	bool readY = false;
	for (unsigned b = 1; b < ratio.size(); b++) {
		if (int(ratio[b]) < 58 && int(ratio[b]) > 47) {
			tempInt = tempInt + ratio[b];
		}
		else {
			if (readY == false) {
				windowInit.ratioInts.a = stoi(tempInt);
				readY = true;
			}
			else {
				windowInit.ratioInts.b = stoi(tempInt);
				readY = false;
			}
			tempInt = "";
		}
	}
	bool set = false;
	for (unsigned b = 0; b < resolution.size(); b++) {
		if (int(resolution[b]) < 58 && int(resolution[b]) > 47) {
			tempInt = tempInt + resolution[b];
		}
		else {
			set = true;
		}
		if (b == resolution.size() - 1) {
			set = true;
		}
		if(set == true){
			set = false;
			if (readY == false) {
				windowInit.resolutionInts.a = stoi(tempInt);
				readY = true;
			}
			else {
				windowInit.resolutionInts.b = stoi(tempInt);
				readY = false;
			}
			tempInt = "";
		}
	}
	return(windowInit);
}

void WINDOW::GenorateFromSettings()
{
	windowSettings = LoadWindowSettings();
	GenorateWindow(windowSettings.programName, windowSettings.resolutionInts.a, windowSettings.resolutionInts.b);
	LOGGING::Log(5, "Version: " + to_string(windowSettings.versionNumber.majorVersion) + "." + to_string(windowSettings.versionNumber.minorVersion) + "." + to_string(windowSettings.versionNumber.subVersion), "Window.cpp/GenorateFromString");
	LOGGING::Log(5, "Window Ratio:" + to_string(windowSettings.ratioInts.a) + ":" + to_string(windowSettings.ratioInts.b), "Window.cpp/GenorateFromSettings");
	LOGGING::Log(5, "Window Resolution: " + to_string(windowSettings.resolutionInts.a) + "x" + to_string(windowSettings.resolutionInts.b), "Window.cpp/GenorateFromSettings");
}

void WINDOW::DestroyCurrentWindow()
{
	glutDestroyWindow(mainWindow);
	LOGGING::Log(1, "Destroyed current window", "Window.cpp/DestoryCurrentWindow");
}
