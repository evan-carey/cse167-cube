#pragma once
#include "ObjReader.h"
#include "Matrix4.h"
#include "GL\glut.h"

class PointCloud {
protected:
	char* fileName; // path to file containing data for PointCloud object
	vector<Point3D> pos; // Positions of points. Each point has x, y, and z
	vector<Point3D> norm; // Postions that specify the normal vectors. Each point has x, y, and z
	bool visible;

	Matrix4 model2world;
	double angle;

	Vector3 center;

public:
	PointCloud();
	PointCloud(char* fileName);
	virtual ~PointCloud();

	void createFromFile(char* fileName);

	int length(); // return length of vectors or -1 if they differ (indicating an error)

	Point3D getNorm(int index) {
		if (index < 0 || index > norm.size()) return NULL;
		return norm.at(index);
		//return norm[index];
	}

	Point3D getPos(int index) {
		if (index < 0 || index > pos.size()) return NULL;
		return pos.at(index);
		//return pos[index];
	}
	void setVisible(bool v) { visible = v; }
	bool isVisible() { return visible; }


	Matrix4& getMatrix() { return model2world; }
	void setMatrix(Matrix4& m) { model2world = Matrix4(m); }

	double getAngle() { return angle; }
	void setAngle(double a) { angle = a; }

	void normalizeNorm();

	void renderModel();
	void renderScaledModel(double);

	// functions to calculate min and max points in model
	void calcMinMax();

	void translateToOrigin();
};

