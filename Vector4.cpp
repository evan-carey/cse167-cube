#include "Vector4.h"

using namespace std;

Vector4 Vector4::operator+(const Vector4& other) {
	return Vector4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

Vector4 Vector4::operator-(const Vector4& other) {
	return Vector4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

double Vector4::operator[](const int i) {
	return this->get(i);
}

void Vector4::set(double x0, double y0, double z0, double w0) {
	x = x0;
	y = y0;
	z = z0;
	w = w0;
}

double Vector4::get(int i) const {
	switch (i) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default: printf("Error: Invalid index.\n"); return -1.0;
	}
}

double Vector4::length() {
	return sqrt(x*x + y*y + z*z + w*w);
}

void Vector4::dehomogenize() {
	if (w != 0.0) {
		x /= w;
		y /= w;
		z /= w;
		w = 1.0;
	}
}

void Vector4::print(std::string comment) {
	printf("%s (%.2f, %.2f, %.2f, %.2f)\n", comment.c_str(), x, y, z, w);
}