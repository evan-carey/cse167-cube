#include "PointCloud.h"

PointCloud::PointCloud() {
	fileName = NULL;
	pos = vector<Point3D>();
	norm = vector<Point3D>();
	visible = false;
	model2world = Matrix4();
	model2world.identity();
	scale = 1.0;
}

PointCloud::PointCloud(char* fileName) {
	this->fileName = fileName;
	visible = false;
	ObjReader::readObj(fileName, pos, norm);
	normalizeNorm();
	model2world = Matrix4();
	model2world.identity();
	calcMinMax();
	calcCenter();
	translateToOrigin();
	scale = 1.0;
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
	model2world.identity();

	calcMinMax();
	printMinMax();
	calcCenter();

	translateToOrigin();
	makeScaleToFitWindow();
}

int PointCloud::length() {
	return pos.size() == norm.size() ? pos.size() : -1;
}

void PointCloud::normalizeNorm() {
	for (vector<Point3D>::iterator it = norm.begin(); it != norm.end(); ++it) {
		it->normalize();
	}
}

//void PointCloud::renderModel() {
//	for (int i = 0; i < this->length(); ++i) {
//		
//		glColor3f(this->getNorm(i).getx(), this->getNorm(i).gety(), this->getNorm(i).getz());
//
//		glNormal3d(this->getNorm(i).getx(), this->getNorm(i).gety(), this->getNorm(i).getz());
//		glVertex3d(this->getPos(i).getx(), this->getPos(i).gety(), this->getPos(i).getz());
//		
//	}
//}

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
}

void PointCloud::calcCenter() {
	center = Vector3(((maxX - minX) / 2.0) + minX, 
					((maxY - minY) / 2.0) + minY, 
					((maxZ - minZ) / 2.0) + minZ);
}

void PointCloud::translateToOrigin() {
	Matrix4 tm = Matrix4(1.0, 0.0, 0.0, -center.getX(),
						0.0, 1.0, 0.0, -center.getY(),
						0.0, 0.0, 1.0, -center.getZ(),
						0.0, 0.0, 0.0, 1.0);

	tm.print("\nTranslation matrix:");

	model2world *= tm;

	for (vector<Point3D>::iterator it = pos.begin(); it != pos.end(); ++it) {
		*it = tm * *it;
	}
}

void PointCloud::printMinMax() {
	printf("\nMin X: %f \tMax X: %f\n", minX, maxX);
	printf("Min Y: %f \tMax Y: %f\n", minY, maxY);
	printf("Min Z: %f \tMax Z: %f\n", minZ, maxZ);
}

void PointCloud::makeScale(double s) {
	model2world.makeScale(s, s, s);
}

void PointCloud::makeScaleToFitWindow() {
	double theta = 30.0;
	theta = (theta / 180.0) * M_PI;
	double adj = 20.0;

	double op = adj * tan(theta);
	double windowWidth = op * 2.0;

	double scaleFactor = windowWidth / (maxX - minX);

	Matrix4 sm = Matrix4(scaleFactor, 0.0, 0.0, 0.0,
						0.0, scaleFactor, 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0, // sm[2][2] == 1.0 so the model won't be brought closer to the camera
						0.0, 0.0, 0.0, 1.0);

	sm.print("Scale Matrix:");

	model2world *= sm;
}