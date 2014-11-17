#pragma once

#include "Plane.h"
#include "Matrix4.h"
#include "Camera.h"


enum planes {NEAR, FAR, LEFT, RIGHT, TOP, BOTTOM};
class Frustum {
private:
	float fov, aspect, near, far;
	Matrix4 projection;
public:
	Frustum(float, float, float, float);
	~Frustum();
	Matrix4 projectionMatrix(double fov, double aspect, double near, double far);
	Matrix4 getProjectionMatrix() { return projection; }

	void setGLMatrix() { glMultMatrixd(projection.getPointer()); }

	float getFOV() { return fov; }
	void setFOV(float f) { fov = f; }

	float getAspect() { return aspect; }
	void setAspect(float a) { aspect = a; }

	float getNear() { return near; }
	void setNear(float n) { near = n; }

	float getFar() { return far; }
	void setFar(float f) { far = f; }

	void init(Camera*, Plane*);

};

