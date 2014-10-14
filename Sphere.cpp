#include "Sphere.h"


Sphere::Sphere() {
	velocity = 0.0;
}

Sphere::Sphere(Vector3& v) {
	velocity = v;
}

Sphere::Sphere(Sphere& other) {
	velocity = other.velocity;
}

Sphere::~Sphere() {
}

void Sphere::setVelocity(const Vector3& v) {
	velocity = v;
}

Vector3 Sphere::getVelocity() {
	return velocity;
}