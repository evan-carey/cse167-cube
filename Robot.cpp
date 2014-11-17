#include "Robot.h"
#include "WalkingAnimation.h"
#include <math.h>
using namespace std;


const double Robot::BODY_SIZE_X = 2.0;
const double Robot::BODY_SIZE_Y = 3.0;
const double Robot::BODY_SIZE_Z = 2.0;

const double Robot::HEAD_RADIUS = 0.7;

const double Robot::ARM_SIZE_X = 0.5;
const double Robot::ARM_SIZE_Y = 4.0;
const double Robot::ARM_SIZE_Z = 0.5;

const double Robot::LEG_SIZE_X = 0.5;
const double Robot::LEG_SIZE_Y = 4.0;
const double Robot::LEG_SIZE_Z = 0.5;

Robot::Robot(Matrix4& c, bool walk) : walking(walk) {
	root = new MatrixTransform(c);
	boundingSphere = new BoundingSphere();
	boundingSphere->setRadius(BODY_SIZE_Y / 2.0 + HEAD_RADIUS * 2.0);
	init(c);
	
}


Robot::~Robot() {
	delete root;
}

void Robot::draw(Matrix4 C) {
	
	root->draw(C);
}

void Robot::init() {
	Matrix4 c;
	c.identity();
	init(c);
}

void Robot::init(Matrix4 c) {
	// Body
	body = new GLCube("Body", BODY_SIZE_X, BODY_SIZE_Y, BODY_SIZE_Z);
	Matrix4 tm;
	tm = c;
	MatrixTransform *bodyTransform = new MatrixTransform(tm);
	bodyTransform->addChild(body);

	// Head
	head = new GLSphere("Head", HEAD_RADIUS);
	tm = c;
	tm.makeTranslate(0.0, BODY_SIZE_Y / 2.0 + HEAD_RADIUS, 0.0); // move up to where center of head will be
	MatrixTransform* headTransform = new MatrixTransform(tm);
	headTransform->addChild(head);
	

	// Left Arm
	leftArm = new GLCube("Left Arm", ARM_SIZE_X, ARM_SIZE_Y, ARM_SIZE_Z);
	tm = c;	
	// translate
	tm.makeTranslate(-(BODY_SIZE_X / 2.0) - ARM_SIZE_X / 2.0, BODY_SIZE_Y / 2.0 - ARM_SIZE_Y / 2.0, 0.0);
	MatrixTransform* leftArmTransform = new MatrixTransform(tm);
	// rotate
	if (walking) {
		Vector3 leftShoulder(-BODY_SIZE_X / 2.0, BODY_SIZE_Y / 2.0, 0.0);
		WalkingAnimation* leftArmAnimation = new WalkingAnimation(-30.0, 30.0, leftShoulder, 1.0, 0.0);
		leftArmAnimation->addChild(leftArm);
		leftArmTransform->addChild(leftArmAnimation);

	} else {
		leftArmTransform->addChild(leftArm);
	}

	// Right Arm
	rightArm = new GLCube("Right Arm", ARM_SIZE_X, ARM_SIZE_Y, ARM_SIZE_Z);
	tm = c;
	// translate
	tm.makeTranslate(BODY_SIZE_X / 2.0 + ARM_SIZE_X / 2.0, (BODY_SIZE_Y / 2.0) - (ARM_SIZE_Y / 2.0), 0.0);
	MatrixTransform* rightArmTransform = new MatrixTransform(tm);
	// rotate
	if (walking) {
		Vector3 rightShoulder(BODY_SIZE_X / 2.0, BODY_SIZE_Y / 2.0, 0.0);
		WalkingAnimation* rightArmAnimation = new WalkingAnimation(-30.0, 30.0, rightShoulder, -1.0, 0.0);
		rightArmAnimation->addChild(rightArm);
		rightArmTransform->addChild(rightArmAnimation);
	} else {
		rightArmTransform->addChild(rightArm);
	}

	// Left Leg
	leftLeg = new GLCube("Left Leg", LEG_SIZE_X, LEG_SIZE_Y, LEG_SIZE_Z);
	tm = c;
	// translate
	tm.makeTranslate(-(BODY_SIZE_X / 2.0) + LEG_SIZE_X, -(BODY_SIZE_Y / 2.0) - (LEG_SIZE_Y / 2.0), 0.0);
	MatrixTransform* leftLegTransform = new MatrixTransform(tm);
	// rotate
	if (walking) {
		Vector3 leftHip(BODY_SIZE_X / 2.0, BODY_SIZE_Y / 2.0, 0.0);
		WalkingAnimation* leftLegAnimation = new WalkingAnimation(-30.0, 30.0, leftHip, -1.0, 0.0);
		leftLegAnimation->addChild(leftLeg);
		leftLegTransform->addChild(leftLegAnimation);
	} else {
		leftLegTransform->addChild(leftLeg);
	}

	// Right Leg
	rightLeg = new GLCube("Right Leg", LEG_SIZE_X, LEG_SIZE_Y, LEG_SIZE_Z);
	tm = c;
	// translate
	tm.makeTranslate(BODY_SIZE_X / 2.0 - LEG_SIZE_X, -(BODY_SIZE_Y / 2.0) - (LEG_SIZE_Y / 2.0), 0.0);
	MatrixTransform* rightLegTransform = new MatrixTransform(tm);
	// rotate
	if (walking) {
		Vector3 rightHip(-BODY_SIZE_X / 2.0, BODY_SIZE_Y / 2.0, 0.0);
		WalkingAnimation* rightLegAnimation = new WalkingAnimation(-30.0, 30.0, rightHip, 1.0, 0.0);
		rightLegAnimation->addChild(rightLeg);
		rightLegTransform->addChild(rightLegAnimation);
	} else {
		rightLegTransform->addChild(rightLeg);
	}

	// Add all to root
	root->addChild(bodyTransform);
	root->addChild(headTransform);
	root->addChild(leftArmTransform);
	root->addChild(rightArmTransform);
	root->addChild(leftLegTransform);
	root->addChild(rightLegTransform);

	
}

void Robot::setBoundingSphere(double minX, double maxX, double minY, double maxY, double minZ, double maxZ) {
	Vector3 center = Vector3(((maxX - minX) / 2.0) + minX,
		((maxY - minY) / 2.0) + minY,
		((maxZ - minZ) / 2.0) + minZ);

	double l = maxX - minX;
	double w = maxY - minY;
	double d = maxZ - minZ;

	float radius = sqrt((l / 2.0)*(l / 2.0) + (w / 2.0)*(w / 2.0) + (d / 2.0)*(d / 2.0));
	boundingSphere->set(center, radius);
}