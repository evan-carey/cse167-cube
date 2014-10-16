#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include "cube.h"
#include "Sphere.h"
#include <ostream>

namespace Globals { 
	extern Cube cube; 
	extern Sphere sphere;
};

class InputHandler {
public:
	InputHandler();
	~InputHandler();
	
	static void processNormalKeys(unsigned char key, int x, int y);
};

#endif