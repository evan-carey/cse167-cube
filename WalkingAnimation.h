#pragma once

#include "Group.h"

/* Simulate walking by applying rotation matrices (used by Robot) */
class WalkingAnimation : public Group {
private:
	double rotationIncrement;
	double currentAngle;
	double minAngle, maxAngle;
	Vector3 axis;
	Matrix4 rm;
public:
	WalkingAnimation(double min, double max, const Vector3& axis, double startAngle, double current);
	WalkingAnimation(double min, double max, const Vector3& axis, const Matrix4& m, double startAngle, double current);
	virtual ~WalkingAnimation();

	void draw(Matrix4);
	void update();
	void update(Matrix4);
};

