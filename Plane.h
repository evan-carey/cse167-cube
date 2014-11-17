#pragma once
#include "Vector3.h"

class Plane {
private:
	float width, height;
	Vector3 point, normal;
public:
	Plane();
	Plane(float w, float h, Vector3& p, Vector3& n) : width(w), height(h), point(p), normal(n) {}
	~Plane();

	void setPoint(Vector3& p) { point = p; }
	Vector3& getPoint() { return point; }

	void setNormal(Vector3& n) { normal = n; }
	Vector3& getNormal() { return normal; }

	void setWidth(float w) { width = w; }
	float getWidth() { return width; }

	void setHeight(float h) { height = h; }
	float getHeight() { return height; }

	float distance(Vector3& p) { Vector3 dist = p - point; return dist.dot(normal); }
};

