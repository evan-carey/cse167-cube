#include "PointCloud.h"

PointCloud::PointCloud() {
	fileName = NULL;
	pos = vector<Point3D>();
	norm = vector<Point3D>();
	visible = false;
	model2world = Matrix4();
}


PointCloud::PointCloud(char* fileName) {
	this->fileName = fileName;
	visible = false;
	ObjReader::readObj(fileName, pos, norm);
	normalizeNorm();
	model2world = Matrix4();
	calcMinMax();
	calcCenter();
	translateToOrigin();
}


PointCloud::~PointCloud() {
	pos.clear();
	norm.clear();
}



void PointCloud::createFromFile(char* fileName) {
	this->fileName = fileName;
	visible = false;
	ObjReader::readObj(fileName, pos, norm);
	normalizeNorm();
	model2world = Matrix4();
	calcMinMax();
	calcCenter();
	translateToOrigin();
}

int PointCloud::length() {
	return pos.size() == norm.size() ? pos.size() : -1;
}

void PointCloud::normalizeNorm() {
	for (vector<Point3D>::iterator it = norm.begin(); it != norm.end(); ++it) {
		it->normalize();
	}
}

void PointCloud::renderModel() {
	for (int i = 0; i < this->length(); ++i) {
		
		glColor3f(this->getNorm(i).getx(), this->getNorm(i).gety(), this->getNorm(i).getz());

		glNormal3d(this->getNorm(i).getx(), this->getNorm(i).gety(), this->getNorm(i).getz());
		glVertex3d(this->getPos(i).getx(), this->getPos(i).gety(), this->getPos(i).getz());
		
	}
}

void PointCloud::renderScaledModel(double s) {
	for (int i = 0; i < this->length(); ++i) {

		glColor3f(this->getNorm(i).getx(), this->getNorm(i).gety(), this->getNorm(i).getz());

		glNormal3d(this->getNorm(i).getx(), this->getNorm(i).gety(), this->getNorm(i).getz());
		glVertex3d(this->getPos(i).getx()*s, this->getPos(i).gety()*s, this->getPos(i).getz()*s);
		
		translateToOrigin(s);
	}
}

void PointCloud::calcMinMax() {
	// Minimums
	minX = minY = minZ = numeric_limits<double>::max();
	// Maximums
	maxX = maxY = maxZ = numeric_limits<double>::min();

	
	for (vector<Point3D>::iterator it = pos.begin(); it != pos.end(); ++it) {
		// X
		if (it->getx() < minX) minX = it->getx();
		if (it->getx() > maxX) maxX = it->getx();
		
		// Y
		if (it->gety() < minY) minY = it->gety();
		if (it->gety() > maxY) maxY = it->gety();

		// Z
		if (it->getz() < minZ) minZ = it->getz();
		if (it->getz() > maxZ) maxZ = it->getz();
	}

	//translateToOrigin();
}

void PointCloud::calcCenter() {
	center = Vector3((minX + maxX) / 2.0, (minY + maxY) / 2.0, (minZ + maxZ) / 2.0);
}

void PointCloud::translateToOrigin() {
	if (center.getX() == 0.0 && center.getY() == 0.0 && center.getZ() == 0.0) return;
	model2world.makeTranslate(-center.getX(), -center.getY(), -center.getZ());
	setCenter(0, 0, 0);
}

void PointCloud::translateToOrigin(double s) {
	if (center.getX() == 0.0 && center.getY() == 0.0 && center.getZ() == 0.0) return;
	model2world.makeTranslate(-s * center.getX(), -s * center.getY(), -s * center.getZ());
	setCenter(0, 0, 0);
}

void PointCloud::printMinMax() {
	printf("Min X: %f \tMax X: %f\n", minX, maxX);
	printf("Min Y: %f \tMax Y: %f\n", minY, maxY);
	printf("Min Z: %f \tMax Z: %f\n", minZ, maxZ);
}