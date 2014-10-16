#include "Cube.h"
#include "Matrix4.h"

using namespace std;

Cube::Cube(){
  angle = 0.0;
  spinAngle = 1.0;
  visible = true;

  color = { 0.0, 1.0, 0.0 };
}

Matrix4& Cube::getMatrix() {
  return model2world;
}

void Cube::setMatrix(Matrix4& m) {
	model2world = Matrix4(m);
}

void Cube::spin(double deg) { // deg is in degrees
  model2world.makeRotateY(deg);   // This creates the matrix to rotate the cube
}

double Cube::getAngle() {
	return angle;
}

void Cube::setAngle(double a) {
	angle = a;
}

double Cube::getSpinAngle() {
	return spinAngle;
}

void Cube::setSpinAngle(double sa) {
	spinAngle = sa;
}

void Cube::orbitZ(double deg) {
	model2world.makeOrbitZ(deg);
}

void Cube::resetPosition() {
	angle = 0.0;
	model2world.identity();
}

float Cube::getRed() {
	return color.red;
}

float Cube::getGreen() {
	return color.green;
}

float Cube::getBlue() {
	return color.blue;
}

void Cube::setColor(float r, float g, float b) {
	this->color.red = r;
	this->color.green = g;
	this->color.blue = b;
}

bool Cube::isVisible() {
	return visible;
}

void Cube::setVisible(bool v) {
	visible = v;
}