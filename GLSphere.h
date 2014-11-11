#pragma once
#include "Geode.h"

class GLSphere : public Geode {
protected:
	GLdouble radius;
	GLint slices; // longitude
	GLint stacks; // latitude
	bool visible;
	bool solid;

	struct COLOR {
		float r;
		float g;
		float b;
	} color;
public:
	GLSphere(char* n = "", GLdouble rad = 1.0, GLint sl = 25, GLint st = 25, 
			bool visible = true, bool solid = true);
	~GLSphere();

	void setRadius(GLdouble rad) { radius = rad; }
	void setColor(float r, float g, float b) { color.r = r; color.g = g; color.b = b; }
	void setVisible(bool v) { visible = v; }

	bool isVisible() { return visible; }
	GLdouble getRadius() { return radius; }

	void draw(Matrix4);

	void render();
};

