#pragma once
#include "Vector3.h"

class BoundingSphere {
private:
	Vector3 center;
	float radius;
public:
	BoundingSphere();
	BoundingSphere(Vector3& center, float radius);
	BoundingSphere(double x, double y, double z, float radius);
	~BoundingSphere();

	Vector3& getCenter() { return center; }
	void setCenter(double x, double y, double z) { center.set(x, y, z); }

	float getRadius() { return radius; }
	void setRadius(float radius) { this->radius = radius; }

	bool isInBounds(Vector3& p, Vector3& n);
};

