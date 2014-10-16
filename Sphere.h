#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Vector3.h"
#include "Matrix4.h"
#include "Window.h"

class Sphere {
protected:
	double radius;
	Vector4 velocity;
	bool visible;
	Matrix4 model2world;
	double spinAngle;

	struct COLOR {
		float red;
		float green;
		float blue;
	} color;

public:
	Sphere();
	Sphere(double, Vector4&, bool, double, float, float, float);
	Sphere(Sphere&);

	virtual ~Sphere();

	void setRadius(double);
	double getRadius();

	void setVelocity(const Vector4&);
	Vector4 getVelocity();

	void setVisible(bool);
	bool isVisible();

	Matrix4& getMatrix();
	void setMatrix(Matrix4& m);

	float getRed();
	float getGreen();
	float getBlue();

	void setColor(float, float, float);

	void setSpinAngle(double);
	double getSpinAngle();

	void spin(double degrees);

	void move();

	void checkCollisions();

	void resetSphere();
};

#endif