#include "Camera.h"


Camera::Camera() {
	set(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

Camera::Camera(Vector3& e, Vector3& d, Vector3& up) {
	this->e = e;
	this->d = d;
	this->up = up;

	c = initCamera();
}

Camera::~Camera() {
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up) {
	this->e = e;
	this->d = d;
	this->up = up;

	c = initCamera();
}

GLdouble* Camera::getGLMatrix() {

	GLdouble glm[16];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			glm[(i*4)+j] = c.get(j, i);
		}
	}
	return &glm[0];
}

Matrix4 Camera::initCamera() {

	Vector3 x, y, z;

	// z-axis -> z = (e - d) / |e - d|
	z = e - d;
	z.normalize();

	// x-axis -> x = (up X z) / |up X z|
	x.cross(up, z);
	x.normalize();

	// y-axis -> y = z X x
	y.cross(z, x);

	// create camera matrix
	Matrix4 m(x.get(0), y.get(0), z.get(0), e.get(0),
			  x.get(1), y.get(1), z.get(1), e.get(1),
			  x.get(2), y.get(2), z.get(2), e.get(2),
			  0.0, 0.0, 0.0, 1.0);

	Matrix4 cinv;
	Matrix4 rinv(m.get(0,0), m.get(0,1), m.get(0,2), 0.0, 
				 m.get(1,0), m.get(1,1), m.get(1,2), 0.0, 
				 m.get(2,0), m.get(2,1), m.get(2,2), 0.0, 
				 0.0, 0.0, 0.0, 1.0);
	rinv.transpose();
	//rinv.print("RINV:");

	Matrix4 tinv(1.0, 0.0, 0.0, -e.get(0), 
				0.0, 1.0, 0.0, -e.get(1), 
				0.0, 0.0, 1.0, -e.get(2), 
				0.0, 0.0, 0.0, 1.0);

	cinv = rinv * tinv;
	//cinv.print("Cinv: ");
	return cinv;
}