#include "Vector3.h"

using namespace std;

Vector3 Vector3::operator+(const Vector3& other) {
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) {
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

double Vector3::operator[](const int i) {
	return this->get(i);
}

void Vector3::set(double x0, double y0, double z0) {
	x = x0;
	y = y0;
	z = z0;
}

double Vector3::get(int i) {
	switch (i) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: printf("Error: Invalid index.\n"); return -1.0;
	}
}

void Vector3::negate() {
	x = -x;
	y = -y;
	z = -z;
}

void Vector3::scale(double s) {
	x *= s;
	y *= s;
	z *= s;
}

double Vector3::dot(const Vector3& b) {
	return x * b.x + y * b.y + z * b.z;
}

double Vector3::dot(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;

	return Vector3(x, y, z);
}

double Vector3::length() {
	return sqrt(x*x + y*y + z*z);
}

void Vector3::normalize() {
	double len = length();
	if (len <= 0.0) return;
	scale(1.0 / len);
}

void Vector3::print(std::string comment) {
	printf("%s (%.2f, %.2f, %.2f)\n", comment.c_str(), x, y, z);
}