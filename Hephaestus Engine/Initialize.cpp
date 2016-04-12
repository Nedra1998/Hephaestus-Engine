#include "stdlibraries.h"
#include "Initialize.h"
using namespace std;


void INITIALIZE::InitializeLogging(string programName)
{
	LOGGING::Initilize(programName);
}
void INITIALIZE::GLUTInitialize(int argc, char ** argv)
{
	glutInit(&argc, argv);
	LOGGING::Log(1, "Initilized GLUT", "Initilize.cpp/GLUTInitilize");
}

void INITIALIZE::InitializeGl3W()
{
	if (gl3wInit()) {
		LOGGING::Log(4, "Could not initialize gl3w", "Initialize.cpp/InitializeGL3W");
	}
	else {
		LOGGING::Log(1, "Initialized gl3w", "Initialize.cpp/InitializeGL3W");
	}
	if (!gl3wIsSupported(3, 3)) {
		LOGGING::Log(4, "OpenGL version 3.3 is not supported by gl3w", "Initialize.cpp/InitializeGL3W");
	}
	else {
		LOGGING::Log(1, "Loaded OpenGL version 3.3", "Initialize.cpp/InitializeGL3W");
	}
}


unsigned int INITIALIZE::Defaults(unsigned int displayMode, int & width, int & height)
{
	return(displayMode);
}
