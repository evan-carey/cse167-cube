#pragma once
#include "Sphere.h"
#include "cube.h"
#include "MatrixTransform.h"
#include "BoundingSphere.h"

class Robot {
protected:
	Sphere* head;
	Cube* body;
	Cube* leftArm, rightArm;
	Cube* leftLeg, rightLeg;

	MatrixTransform root;

	BoundingSphere* boundingSphere;

public:
	Robot();
	~Robot();

	void draw(MatrixTransform);
};

