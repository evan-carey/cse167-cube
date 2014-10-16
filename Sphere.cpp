#include "Sphere.h"


Sphere::Sphere() {
	radius = 2.5;
	velocity = Vector4(0.2, 0.2, 0.2, 1.0);
	visible = false;
	color = { 1.0, 0.0, 0.0 };
	spinAngle = 1.0;
}

Sphere::Sphere(double radius, Vector4& v, bool visible, double spinAngle, float r, float g, float b) {
	this->radius = radius;
	velocity = v;
	this->visible = visible;
	this->spinAngle = spinAngle;
	setColor(r, g, b);
}

Sphere::Sphere(Sphere& other) {
	this->radius = other.radius;
	this->velocity = other.velocity;
	this->visible = other.visible;
	this->spinAngle = other.spinAngle;
	setColor(other.getRed(), other.getGreen(), other.getBlue());
}

Sphere::~Sphere() {
}

void Sphere::setRadius(double radius) {
	this->radius = radius;
}
double Sphere::getRadius() {
	return radius;
}

void Sphere::setVelocity(const Vector4& velocity) {
	this->velocity = velocity;
}

Vector4 Sphere::getVelocity() {
	return velocity;
}

void Sphere::setVisible(bool visible) {
	this->visible = visible;
}

bool Sphere::isVisible() {
	return visible;
}

Matrix4& Sphere::getMatrix() {
	return model2world;
}

void Sphere::setMatrix(Matrix4& m) {
	model2world = Matrix4(m);
}
float Sphere::getRed() {
	return color.red;
}

float Sphere::getGreen() {
	return color.green;
}

float Sphere::getBlue() {
	return color.blue;
}

void Sphere::setColor(float r, float g, float b) {
	this->color.red = r;
	this->color.green = g;
	this->color.blue = b;
}

double Sphere::getSpinAngle() {
	return spinAngle;
}

void Sphere::setSpinAngle(double sa) {
	spinAngle = sa;
}

void Sphere::spin(double deg) { // deg is in degrees
	model2world.makeRotateY(deg);   // This creates the matrix to rotate the cube
}

void Sphere::move() {
	model2world.makeTranslate(velocity.getX(), velocity.getY(), velocity.getZ());

	checkCollisions();
}

void Sphere::checkCollisions() {
	// X - check right wall
	if (model2world.get(0, 3) > 10.0) {
		velocity.setX(-1.0 * velocity.getX());
	}
	// X - check left wall
	if (model2world.get(0, 3) < -10.0) {
		velocity.setX(-1.0 * velocity.getX());
	}
	// Y - check upper wall
	if (model2world.get(1, 3) > 8.0) {
		velocity.setY(-1.0 * velocity.getY());
	}
	// Y - check lower wall
	if (model2world.get(1, 3) < -8.0) {
		velocity.setY(-1.0 * velocity.getY());
	}
	// Z - check front wall
	if (model2world.get(2, 3) > 6.0) {
		velocity.setZ(-1.0 * velocity.getZ());
	}
	// Z - check back wall
	if (model2world.get(2, 3) < -20.0) {
		velocity.setZ(-1.0 * velocity.getZ());
	}
}

void Sphere::resetSphere() {
	// radius = 2.5;
	velocity.set(0.2, 0.2, 0.2, 1.0);
	// velocity = Vector4(0.2, 0.2, 0.2, 1.0);
	//visible = false;
	//color = { 1.0, 0.0, 0.0 };
	//spinAngle = 1.0;
	model2world.identity();
}