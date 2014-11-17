#pragma once
#include "GLSphere.h"
#include "GLCube.h"
#include "MatrixTransform.h"
#include "BoundingSphere.h"
#include "Matrix4.h"

class Robot : public Node {
private:
	static const double BODY_SIZE_X, BODY_SIZE_Y, BODY_SIZE_Z;
	static const double HEAD_RADIUS;
	static const double ARM_SIZE_X, ARM_SIZE_Y, ARM_SIZE_Z;
	static const double LEG_SIZE_X, LEG_SIZE_Y, LEG_SIZE_Z;

	GLSphere* head;
	GLCube* body;
	GLCube* leftArm, *rightArm;
	GLCube* leftLeg, *rightLeg;

	MatrixTransform* root;
	Node* robot;

	double width, height, depth;

	bool walking;

	BoundingSphere* boundingSphere;

public:
	Robot(Matrix4&, bool walk = true);
	~Robot();

	void draw(Matrix4);

	void init();
	void init(Matrix4);

	void setBoundingSphere(double, double, double, double, double, double);

};

