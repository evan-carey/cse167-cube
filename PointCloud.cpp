#include "PointCloud.h"

PointCloud::PointCloud() {
	fileName = NULL;
	pos = vector<Point3D>();
	norm = vector<Point3D>();
	visible = false;
}


PointCloud::PointCloud(char* fileName) {
	this->fileName = fileName;
	visible = false;
	ObjReader::readObj(fileName, pos, norm);
	normalizeNorm();
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
}

int PointCloud::length() {
	return pos.size() == norm.size() ? pos.size() : -1;
}

void PointCloud::normalizeNorm() {
	for (vector<Point3D>::iterator it = norm.begin(); it != norm.end(); ++it) {
		it->normalize();
	}
}