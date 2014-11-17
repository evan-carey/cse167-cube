#include "GLCube.h"
#include "main.h"


GLCube::GLCube(char* n, GLdouble x, GLdouble y, GLdouble z) {
	name = n;
	boundingSphere = new BoundingSphere();
	setSize(x, y, z);
	setBoundingSphere(x, y, z);
	visible = true;
	
}

GLCube::GLCube(char* n, GLdouble s) {
	name = n;
	boundingSphere = new BoundingSphere();
	setSize(s, s, s);
	setBoundingSphere(s, s, s);
	visible = true;
}


GLCube::~GLCube() {
	delete boundingSphere;
}

void GLCube::setSize(GLdouble x, GLdouble y, GLdouble z) {
	sizeX = x;
	sizeY = y;
	sizeZ = z;
}

void GLCube::render() {
	if (!isVisible()) return;
	//if (Globals::cullingEnabled && isInBounds(boundingSphere)) {
		//glMatrixMode(GL_MODELVIEW);
		//glPushMatrix();
		glScaled(sizeX, sizeY, sizeZ);
		glColor3f(0.8, 0.8, 0.8);
		glutSolidCube(1.0);
		//glPopMatrix();
	//}
}

void GLCube::setBoundingSphere(double x, double y, double z) {
	/*float radius = fmax(x, y);
	radius = fmax(radius, z);
	radius /= 2.0;*/
	float radius = sqrt(x*x + y*y + z*z) / 2.0;
	boundingSphere->setRadius(radius);
	boundingSphere->setCenter((float)x / 2.0, (float)y / 2.0, (float)z / 2.0);
}