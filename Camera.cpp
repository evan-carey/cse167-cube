#include "Camera.h"


Camera::Camera() {
	c.identity();
}

Camera::Camera(Vector3& e, Vector3& d, Vector3& up) {
	this->e = e;
	this->d = d;
	this->up = up;

	initCameraMatrix();
}

Camera::~Camera() {
}

GLdouble* Camera::getGLMatrix() {
	GLdouble glm[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			glm[i][j] = c.get(j, i);
		}
	}
	return &glm[0][0];
}

void Camera::initCameraMatrix() {
	// z-axis -> z = (e - d) / |e - d|
	Vector3 z = this->e - this->d;
	z.normalize();

	// x-axis -> x = (up X z) / |up X z|
	Vector3 x = x.cross(up, z);
	x.normalize();

	// y-axis -> y = z X x
	Vector3 y = y.cross(z, x);

	// create camera matrix
	c = Matrix4(x.getX(), y.getX(), z.getX(), e.getX(),
		x.getY(), y.getY(), z.getY(), e.getY(),
		x.getZ(), y.getZ(), z.getZ(), e.getZ(),
		0.0, 0.0, 0.0, 1.0);

}