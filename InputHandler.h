#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include "cube.h"
#include "Sphere.h"
#include "Camera.h"
#include "House.h"
#include <ostream>
#include <GL/glut.h>

namespace Globals { 
	extern Cube cube; 
	extern Sphere sphere;
	extern Camera camera;
	extern House house;
};

class InputHandler {
public:
	InputHandler();
	~InputHandler();
	
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int key, int x, int y);
};

#endif