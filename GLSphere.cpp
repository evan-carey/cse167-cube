#include "GLSphere.h"


GLSphere::GLSphere(char* n, GLdouble rad, GLint sl, GLint st, bool visible, bool solid) {
	name = n;
	radius = rad;
	slices = sl;
	stacks = st;

	this->visible = visible;
	this->solid = solid;

	boundingSphere = new BoundingSphere();
	boundingSphere->setRadius(rad);
}


GLSphere::~GLSphere() {
	delete boundingSphere;
}

void GLSphere::setRadius(GLdouble rad) {
	radius = rad;
	boundingSphere->setRadius(rad);
}

void GLSphere::render() {
	if (!isVisible()) return;
	glColor3f(0.8, 0.8, 0.8);
	if (solid) glutSolidSphere(radius, slices, stacks);
	else glutWireSphere(radius, slices, stacks);
}