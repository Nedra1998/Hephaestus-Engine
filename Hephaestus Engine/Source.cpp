#include <iostream>
#include "Libraries.h"
#include "Consolas.h"
using namespace std;

GLuint VBO;
struct Vec3 {
	float x, y, z;
	Vec3() {}

	Vec3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

void RenderSceneCB() {
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void InitizlizeGlutCallBacks() {
	glutDisplayFunc(RenderSceneCB);
}

void CreateVertexBuffer() {
	Vec3 Vertex[1];
	Vertex[0] = Vec3(0, 0, 0);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);
}

void main(int argc, char** argv) {
	Logging::Initilize("Hephaestus Engine V-0.0.1");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Hephaestus Engine");
	InitizlizeGlutCallBacks();
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}
	glClearColor(0.0, 0.0, 0.0, 0.0);
	CreateVertexBuffer();
	glutMainLoop();
	Logging::Terminate();
}