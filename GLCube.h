#pragma once
#include "Geode.h"

class GLCube : public Geode {
protected:
	GLdouble size;
	bool visible;

	struct COLOR {
		float r;
		float g;
		float b;
	} color;
public:
	GLCube(char* n = "", GLdouble size = 1.0);
	~GLCube();

	void setSize(GLdouble size) { this->size = size; }
	void setVisible(bool visible) { this->visible = visible; }
	void setColor(float r, float g, float b) { color.r = r; color.g = g; color.b = b; }

	bool isVisible() { return visible; }
	GLdouble getSize() { return size; }
	
	void draw(Matrix4);
};

