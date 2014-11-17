#pragma once
#include "Geode.h"

class GLCube : public Geode {
protected:
	GLdouble sizeX, sizeY, sizeZ;
	bool visible;

	struct COLOR {
		float r;
		float g;
		float b;
	} color;
public:
	GLCube(char* n = "", GLdouble x = 1.0, GLdouble y = 1.0, GLdouble z = 1.0);
	GLCube(char* n, GLdouble size);
	~GLCube();

	void setSize(GLdouble, GLdouble, GLdouble);
	void setSizeX(GLdouble x) { sizeX = x; }
	void setSizeY(GLdouble y) { sizeY = y; }
	void setSizeZ(GLdouble z) { sizeZ = z; }

	void setVisible(bool visible) { this->visible = visible; }
	void setColor(float r, float g, float b) { color.r = r; color.g = g; color.b = b; }

	void setBoundingSphere(double x, double y, double z);

	bool isVisible() { return visible; }

	
	//void draw(Matrix4);
	void render();
};

