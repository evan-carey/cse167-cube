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
		// printf("norm: ( %f, %f, %f )\n", this->getNorm(i).getx(), this->getNorm(i).gety(), this->getNorm(i).getz());
		// printf("Pos: ( %f, %f, %f )\n", this->getPos(i).getx(), this->getPos(i).gety(), this->getPos(i).getz());
	}
}

void PointCloud::renderScaledModel(double s) {
	for (int i = 0; i < this->length(); ++i) {
		//glColor3f((double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);
		glColor3f(0.0, 0.5, 0.7);
		glNormal3d(this->getNorm(i).getx()*s, this->getNorm(i).gety()*s, this->getNorm(i).getz()*s);
		glVertex3d(this->getPos(i).getx()*s, this->getPos(i).gety()*s, this->getPos(i).getz()*s);
		// printf("norm: ( %f, %f, %f )\n", this->getNorm(i).getx(), this->getNorm(i).gety(), this->getNorm(i).getz());
		// printf("Pos: ( %f, %f, %f )\n", this->getPos(i).getx(), this->getPos(i).gety(), this->getPos(i).getz());
	}
}

void PointCloud::calcMinMax() {
	// Minimums
	double minX, minY, minZ;
	minX = minY = minZ = numeric_limits<double>::max();
	// Maximums
	double maxX, maxY, maxZ;
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

	center = Vector3((minX+maxX)/2.0, (minY+maxY)/2.0, (minZ+maxZ)/2.0);

	printf("Min X: %f \tMax X: %f\n", minX, maxX);
	printf("Min Y: %f \tMax Y: %f\n", minY, maxY);
	printf("Min Z: %f \tMax Z: %f\n", minZ, maxZ);

	translateToOrigin();
}

void PointCloud::translateToOrigin() {
	model2world.makeTranslate(-center.getX(), -center.getY(), -center.getZ());
	model2world.print("Model to World: ");
}