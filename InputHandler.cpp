#include "InputHandler.h"


using namespace std;

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::processNormalKeys(unsigned char key, int x, int y) {
	std::string printString = "";

	switch (key) {
	case 't':
	case 'T':
		// toggle the direction of the spin between clockwise and counterclockwise
		Globals::cube.setSpinAngle(-1.0 * Globals::cube.getSpinAngle());
		printString = "t: Changed rotation direction";
		break;
	case 'x':
		// move cube left by a small amount
		Globals::cube.getMatrix().makeTranslate(-1.0, 0.0, 0.0);
		printString = "x: Moved cube left";
		break;
	case 'X':
		// move cube right by a small amount
		Globals::cube.getMatrix().makeTranslate(1.0, 0.0, 0.0);
		printString = "X: Moved cube right";
		break;
	case 'y':
		// move cube down by a small amount
		Globals::cube.getMatrix().makeTranslate(0.0, -1.0, 0.0);
		printString = "y: Moved cube down";
		break;
	case 'Y':
		// move cube up by a small amount
		Globals::cube.getMatrix().makeTranslate(0.0, 1.0, 0.0);
		printString = "Y: Moved cube up";
		break;
	case 'z':
		// move cube into the screen by a small amount
		Globals::cube.getMatrix().makeTranslate(0.0, 0.0, -1.0);
		printString = "z: Moved cube into the screen";
		break;
	case 'Z':
		// move cube out of the screen by a small amount
		Globals::cube.getMatrix().makeTranslate(0.0, 0.0, 1.0);
		printString = "Z: Moved cube out of the screen";
		break;
	case 'r':
	case 'R':
		// reset cube position, orientation, size, and color
		Globals::cube.resetPosition();
		Globals::cube.setSpinAngle(1.0);
		Globals::cube.setColor(0.0, 1.0, 0.0);
		printString = "r: Reset cube";
		break;
	case 'o':
		// orbit cube counterclockwise about the OpenGL window's z axis by a small number of degrees (e.g., 10)
		Globals::cube.orbitZ(10.0);
		printString = "o: Orbit cube CCW";
		break;
	case 'O':
		// orbit cube clockwise about the OpenGL window's z axis by a small number of degrees (e.g., 10)
		Globals::cube.orbitZ(-10.0);
		printString = "O: Orbit cube CW";
		break;
	case 's':
		// scale cube down (about its center, not the center of the screen)
		Globals::cube.getMatrix().makeScale(.9, .9, .9);
		printString = "s: Scale cube down";
		break;
	case 'S':
		// scale cube up (about its center, not the center of the screen)
		Globals::cube.getMatrix().makeScale(1.1, 1.1, 1.1);
		printString = "S: Scale cube up";
		break;
	case 27: // ESC -> quit
		exit(0);
		break;
	default:
		return;

	}

	// Display the new cube position in the text window
	Vector3 cubePosition(Globals::cube.getMatrix().get(0, 3),
						Globals::cube.getMatrix().get(1, 3),
						Globals::cube.getMatrix().get(2, 3));
	cubePosition.print(printString + "\t\t");
}