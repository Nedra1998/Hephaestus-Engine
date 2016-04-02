#include <iostream>
#include "Libraries.h"
#include "Consolas.h"
using namespace std;
void main() {
	Logging::Initilize("Hephaestus Engine");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Hephaestus Engine");
	glutDisplayFunc(RenderSceneCB);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutMainLoop();
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	Logging::Terminate();
}