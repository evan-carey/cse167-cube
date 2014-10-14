#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Vector3.h"

class Sphere {
protected:
	Vector3 velocity;

public:
	Sphere();
	Sphere(Vector3&);
	Sphere(Sphere&);

	virtual ~Sphere();

	void setVelocity(const Vector3&);
	Vector3 getVelocity();
};

#endif