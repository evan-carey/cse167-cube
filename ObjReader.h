#pragma once
#include "Point3D.h"
#include "Vector3.h"
#include <vector>
using namespace std;

class ObjReader {

public:
	ObjReader();
	virtual ~ObjReader();
	static void readObj(char* fileName, vector<Point3D>& pos, vector<Point3D>& norm);

};

