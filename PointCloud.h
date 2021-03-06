#pragma once
#include "ObjReader.h"
#include "Matrix4.h"

class PointCloud {
protected:
	char* fileName; // path to file containing data for PointCloud object
	vector<Point3D> pos; // Positions of points. Each point has x, y, and z
	vector<Point3D> norm; // Postions that specify the normal vectors. Each point has x, y, and z
	bool visible;

	Matrix4 model2world;
	double angle;

	double minX, minY, minZ;
	double maxX, maxY, maxZ;
	double width, height;
	Vector3 center;

	double scale;

public:
	PointCloud();
	PointCloud(char* fileName);
	virtual ~PointCloud();

	void createFromFile(char* fileName);

	int length(); // return length of vectors or -1 if they differ (indicating an error)

	Point3D getNorm(unsigned int index) {
		if (index < 0 || index > norm.size()) return NULL;
		return norm.at(index);
	}

	Point3D getPos(unsigned int index) {
		if (index < 0 || index > pos.size()) return NULL;
		return pos.at(index);
	}
	void setVisible(bool v) { visible = v; }
	bool isVisible() { return visible; }


	Matrix4& getMatrix() { return model2world; }
	void setMatrix(Matrix4& m) { model2world = Matrix4(m); }

	double getAngle() { return angle; }
	void setAngle(double a) { angle = a; }

	void normalizeNorm();

	// void renderModel();

	Vector3& getCenter() { return center; }
	void setCenter(double x, double y, double z) { center.set(x, y, z); }

	// functions to calculate min and max points in model
	void calcMinMax();
	void calcCenter();
	void translateToOrigin();

	void printMinMax();

	void setScale(double s) { scale = s; }
	double getScale() { return scale; }
	void makeScale(double s);
	void makeScaleToFitWindow();
};

