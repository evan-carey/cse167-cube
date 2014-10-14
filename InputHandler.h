#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include "cube.h"
namespace Globals { extern Cube cube; };

class InputHandler {
public:
	InputHandler();
	~InputHandler();
	
	static void processNormalKeys(unsigned char key, int x, int y);
};

#endif