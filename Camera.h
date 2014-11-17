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
	Matrix4 c_inv;
public:
	Camera();
	Camera(Vector3&, Vector3&, Vector3&);
	virtual ~Camera();

	void set(Vector3& e, Vector3& d, Vector3& up);

	Vector3& getCenterOfProjection() { return e; }
	void setCenterOfProjection(Vector3& e) { this->e = e; set(e, d, up); }
	void setCenterOfProjection(double x, double y, double z) { this->e = Vector3(x, y, z); set(e, d, up); }

	Vector3& getLookAtPoint() { return d; }
	void setLookAtPoint(Vector3& d) { this->d = d; set(e, d, up); }
	void setLookAtPoint(double x, double y, double z) { this->d = Vector3(x, y, z); set(e, d, up); }

	Vector3& getUp() { return up; }
	void setUp(Vector3& up) { this->up = up; set(e, d, up); }
	void setUp(double x, double y, double z) { this->up = Vector3(x, y, z); set(e, d, up); }

	Matrix4& getCameraMatrix() { return c; }
	void setCameraMatrix(Matrix4& c) { this->c = c; }

	Matrix4& getCInv() { return c_inv; }

	GLdouble* getGLMatrix();


	Matrix4 cInv();

	void invert();
	void inverse();

	void translate(double, double, double);

	void reset() {
		set(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));
		//c.identity();
	}
};

