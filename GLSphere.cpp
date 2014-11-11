#include "GLSphere.h"


GLSphere::GLSphere(char* n, GLdouble rad, GLint sl, GLint st, bool visible, bool solid) {
	name = n;
	radius = rad;
	slices = sl;
	stacks = st;

	this->visible = visible;
	this->solid = solid;
}


GLSphere::~GLSphere() {
}

void GLSphere::draw(Matrix4 c) {
	if (solid) glutSolidSphere(radius, slices, stacks);
	else glutWireSphere(radius, slices, stacks);
}