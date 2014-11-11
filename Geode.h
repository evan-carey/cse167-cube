#pragma once
#include "Node.h"
#include "GL/glut.h"

class Geode : public Node {
public:
	Geode(char* name = "");
	virtual ~Geode();

	void draw(Matrix4);

	virtual void render() = 0;
};

