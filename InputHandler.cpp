#include "InputHandler.h"


using namespace std;

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::processNormalKeys(unsigned char key, int x, int y) {
	
	// Cube commands
	if (Globals::cube.isVisible()) {
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
		case 'b':
		case 'B':
			// Switch between cube and sphere
			Globals::cube.setVisible(false);
			Globals::sphere.setVisible(true);
			break;
		case 27: 
			// ESC -> quit
			exit(0);
			break;
		case 'h':
		case 'H':
			// Help menu -> show controls
			std::cout << "\nControls:\n\n"
				<< "* t / T - Toggle the direction of the spin between clockwise and counterclockwise\n"
				<< "* x / X - Move the cube left / right by a small amount\n"
				<< "* y / Y - Move the cube down / up by a small amount\n"
				<< "* z / Z - Move the cube into / out of the screen by a small amount\n"
				<< "* r / R - Reset the cube's position, orientation, size, and color\n"
				<< "* o / O - Orbit the cube counterclockwise / clockwise around the OpenGL window's z-axis by a small number of degrees\n"
				<< "* s / S - Scale the cube down / up\n"
				<< "* b / B - Switch between cube and sphere"
				<< "* ESC - End program\n\n";
			return;
		default:
			std::cout << "Unrecognized command. Press \'h\' for help." << endl;
			return;
		}

		// Display the new cube position in the text window
		Vector3 cubePosition(Globals::cube.getMatrix().get(0, 3),
			Globals::cube.getMatrix().get(1, 3),
			Globals::cube.getMatrix().get(2, 3));
		cubePosition.print(printString + "\t\t");
	}

	// Sphere commands
	else if (Globals::sphere.isVisible()) {
		switch (key) {
		case 'r':
		case 'R':
			// Reset sphere
			Globals::sphere.resetSphere();
			break;
		case 'b':
		case 'B':
			// Switch between cube and sphere
			Globals::cube.setVisible(true);
			Globals::sphere.setVisible(false);
			break;
		case 27:
			// ESC -> quit
			exit(0);
			break;
		case 'h':
		case 'H':
			std::cout << "\nControls:\n\n"
				<< "* r / R - Reset the sphere's position and direction\n"
				<< "* b / B - Switch between cube and sphere"
				<< "* ESC - End program\n\n";
			return;
		default:
			std::cout << "Unrecognized command. Press \'h\' for help." << endl;
			return;
		}
	}

	// Bunny commands
	else if (Globals::bunny.isVisible()) {
		switch (key) {
		case 's':
			// scale cube down (about its center, not the center of the screen)
			Globals::bunny.getMatrix().makeScale(.9, .9, .9);
			break;
		case 'S':
			// scale cube up (about its center, not the center of the screen)
			Globals::bunny.getMatrix().makeScale(1.1, 1.1, 1.1);
			break;
		case 27: exit(0); break;
		default:
			return;
		}
	}
	else {
		switch (key) {
		case 27: exit(0); break;
		default: return;
		}
	}
}

void InputHandler::processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		Globals::cube.setVisible(true);
		Globals::house.setVisible(false);
		Globals::bunny.setVisible(false);
		Globals::dragon.setVisible(false);
		break;
	case GLUT_KEY_F2:
		Globals::camera.set(Vector3(0, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
		Globals::cube.setVisible(false);
		Globals::sphere.setVisible(false);
		Globals::house.setVisible(true);
		Globals::bunny.setVisible(false);
		Globals::dragon.setVisible(false);
		
		break;
	case GLUT_KEY_F3:
		Globals::camera.set(Vector3(-15, 5, 10), Vector3(-5, 0, 0), Vector3(0, 1, 0.5));
		Globals::cube.setVisible(false);
		Globals::sphere.setVisible(false);
		Globals::house.setVisible(true);
		Globals::bunny.setVisible(false);
		Globals::dragon.setVisible(false);
		
		break;
	case GLUT_KEY_F4:
		Globals::camera.reset();
		Globals::cube.setVisible(false);
		Globals::sphere.setVisible(false);
		Globals::house.setVisible(false);
		Globals::bunny.setVisible(true);
		Globals::dragon.setVisible(false);
		Globals::camera.getCameraMatrix().print();
		break;
	case GLUT_KEY_F5:
		Globals::camera.reset();
		Globals::cube.setVisible(false);
		Globals::sphere.setVisible(false);
		Globals::house.setVisible(false);
		Globals::bunny.setVisible(false);
		Globals::dragon.setVisible(true);
		Globals::bunny.calcMinMax();
		Globals::camera.getCameraMatrix().print();
		break;
	default:
		break;
	}
}