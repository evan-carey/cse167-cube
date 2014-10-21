#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include "GL\glut.h"

class Camera {

protected:
	Vector3 e;	// center of projection
	Vector3 d;	// look at point
	Vector3 up; // up vector
	Matrix4 c;	// interal camera matrix
public:
	Camera();
	Camera(Vector3&, Vector3&, Vector3&);
	virtual ~Camera();

	Vector3& getCenterOfProjection() { return e; }
	void setCenterOfProjection(Vector3& e) { this->e = e; }
	void setCenterOfProjection(double x, double y, double z) { this->e = Vector3(x, y, z); }

	Vector3& getLookAtPoint() { return d; }
	void setLookAtPoint(Vector3& d) { this->d = d; }
	void setLookAtPoint(double x, double y, double z) { this->e = Vector3(x, y, z); }

	Vector3& getUp() { return up; }
	void setUp(Vector3& up) { this->up = up; }
	void setUp(double x, double y, double z) { this->up = Vector3(x, y, z); }

	Matrix4& getCameraMatrix() { return c; }
	void setCameraMatrix(Matrix4& c) { this->c = c; }

	GLdouble* getGLMatrix();

	void initCameraMatrix();
};
