#include "Sphere.h"


Sphere::Sphere() {
	radius = 2.5;
	velocity = Vector4(randVelocity(), 1.0, randVelocity(), 1.0);
	visible = false;
	color = { 1.0, 0.0, 0.0 };
	spinAngle = 1.0;
	gravity = -0.07;
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
	velocity.setX(velocity.getX()*0.999);
	velocity.setZ(velocity.getZ()*0.999);
	applyGravity(gravity);
}

void Sphere::checkCollisions() {
	// X - check right wall
	if (model2world.get(0, 3) > 9.0) {
		if (velocity.getX() < 0.1) velocity.setX(0.0);
		else velocity.setX(-0.95 * velocity.getX());
	}
	// X - check left wall
	if (model2world.get(0, 3) < -9.0) {
		if (velocity.getX() > -0.1) velocity.setX(0.0);
		else velocity.setX(-0.95 * velocity.getX());
	}
	// Y - check upper wall
	if (model2world.get(1, 3) > 8.0) {
		velocity.setY(-1.0 * velocity.getY());
	}
	// Y - check lower wall
	if (model2world.get(1, 3) < -7.0) {
		if (velocity.getY() > 0.1 || velocity.getY() < -0.1)
			velocity.setY(-0.95 * velocity.getY());
		else
			velocity.setY(0.0);
		gravity = 0.0;
	} else {
		gravity = -0.07;
	}
	// Z - check front wall
	if (model2world.get(2, 3) > 6.0) {
		if (velocity.getZ() < 0.1) velocity.setZ(0.0);
		else velocity.setZ(-0.95 * velocity.getZ());
	}
	// Z - check back wall
	if (model2world.get(2, 3) < -20.0) {
		if (velocity.getZ() > -0.1) velocity.setZ(0.0);
		else velocity.setZ(-0.95 * velocity.getZ());
	}
}

void Sphere::resetSphere() {
	// radius = 2.5;
	velocity.set(randVelocity(), 1.0, randVelocity(), 1.0);
	// velocity = Vector4(0.2, 0.2, 0.2, 1.0);
	//visible = false;
	//color = { 1.0, 0.0, 0.0 };
	//spinAngle = 1.0;
	model2world.identity();
}

void Sphere::applyGravity(double g) {
	//Vector4 grav = Vector4(0.0, g, 0.0, 1.0);
	//if (velocity.getY() != 0.0)
		velocity.setY(velocity.getY() + g);
}

double Sphere::randVelocity() {
	int direction = rand() % 2 ? 1 : -1;
	double magnitude = ((double) rand() / RAND_MAX) * 0.5;
	return magnitude * direction;
	
}