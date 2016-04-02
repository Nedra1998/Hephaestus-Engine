#include <iostream>
#include "Libraries.h"
#include "Consolas.h"
using namespace std;

void RenderSceneCB() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void InitizlizeGlutCallBacks() {
	glutDisplayFunc(RenderSceneCB);
}

void main(int argc, char** argv) {
	Logging::Initilize("Hephaestus Engine V-0.0.1");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Hephaestus Engine");
	InitizlizeGlutCallBacks();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutMainLoop();
	Logging::Terminate();
}