#pragma once
#include <math.h>
#include <string>

using namespace std;

class Point3D {
protected:
	double x, y, z;

public:
	Point3D(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}
	virtual ~Point3D() {
	}
	void set(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	double getx() { return x; }
	double gety() { return y; }
	double getz() { return z; }

	void setx(double x) { this->x = x; }
	void sety(double y) { this->y = y; }
	void setz(double z) { this->z = z; }

	double length() { return sqrt(x*x + y*y + z*z); }
	void scale(double s) { x *= s; y *= s; z *= s; }
	void normalize() { double l = length(); if (l <= 0.0)return; scale(1.0 / l); }
	
	void print(std::string comment) {
		printf("%s (%.2f, %.2f, %.2f)\n", comment.c_str(), x, y, z);
	}
};

