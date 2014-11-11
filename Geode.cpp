#include "Geode.h"


Geode::Geode(char* name) {
	this->name = name;
}


Geode::~Geode() {
}

void Geode::draw(Matrix4 C) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(C.getPointer());
	render();
}