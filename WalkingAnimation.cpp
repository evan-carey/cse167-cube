#include "WalkingAnimation.h"
#include "Robot.h"


WalkingAnimation::WalkingAnimation(double min, double max, const Vector3& _axis, double startAngle, double current) 
	: minAngle(min), maxAngle(max), axis(_axis), rotationIncrement(startAngle), currentAngle(current) {

	if (currentAngle > maxAngle)
		currentAngle = maxAngle;
	if (currentAngle < minAngle)
		currentAngle = minAngle;

	rm.identity();
	//rm.makeRotate(currentAngle, axis);

}

WalkingAnimation::WalkingAnimation(double min, double max, const Vector3& _axis, const Matrix4& m, double startAngle, double current) 
	: minAngle(min), maxAngle(max), axis(_axis), rm(m), rotationIncrement(startAngle), currentAngle(current) {

	if (currentAngle > maxAngle)
		currentAngle = maxAngle;
	if (currentAngle < minAngle)
		currentAngle = minAngle;

	//rm.makeRotate(currentAngle, axis);
}


WalkingAnimation::~WalkingAnimation() {
}

void WalkingAnimation::draw(Matrix4 m) {

	Matrix4 tm = m * rm;
	for (Node* child : *children) {
		child->draw(tm);
	}
	update();
}

void WalkingAnimation::update() {
	// update angle
	currentAngle += rotationIncrement;

	if (currentAngle >= maxAngle || currentAngle <= minAngle) {
		rotationIncrement = -rotationIncrement;
	}

	// update rotation matrix
	rm.makeTranslate(axis.getX(), axis.getY(), axis.getZ());
	rm.makeRotateX(rotationIncrement);
	rm.makeTranslate(-axis.getX(), -axis.getY(), -axis.getZ());
}

void WalkingAnimation::update(Matrix4 m) {
	// update angle
	currentAngle += rotationIncrement;

	if (currentAngle >= maxAngle || currentAngle <= minAngle) {
		rotationIncrement = -rotationIncrement;
	}

	//Matrix4 t = m;
	
	// update rotation matrix
	//t.makeTranslate(m.get(0, 3), m.get(1, 3), m.get(2, 3));
	rm.makeRotate(rotationIncrement, axis);
	//t.makeTranslate(-m.get(0, 3), -m.get(1, 3), -m.get(2, 3));
}