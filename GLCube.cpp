#include "GLCube.h"


GLCube::GLCube(char* n, GLdouble size) {
	name = n;
	this->size = size;
	
	visible = true;
}


GLCube::~GLCube() {
}

void GLCube::draw(Matrix4 C) {
	glutSolidCube(size);
}