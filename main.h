#ifndef _MAIN_H_
#define _MAIN_H_

#include "Cube.h"
#include "Sphere.h"
#include "Camera.h"
#include "House.h"
#include "PointCloud.h"
#include "Robot.h"
#include "Frustum.h"

const int NUM_ROBOTS = 1000;

namespace Globals {
    extern Cube cube;
	extern Sphere sphere;
	extern Camera* camera;
	extern House house;
	extern PointCloud bunny;
	extern PointCloud dragon;
	extern std::vector<Robot*> robots;
	extern double currentRotationAngle;
	extern bool showBoundingSpheres;
	extern bool cullingEnabled;
	extern Frustum* frustum;
	extern Plane* planes;
};

#endif