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

void INITIALIZE::GLVersion()
{
	
}

unsigned int INITIALIZE::Defaults(unsigned int displayMode, int & width, int & height)
{
	return(displayMode);
}
