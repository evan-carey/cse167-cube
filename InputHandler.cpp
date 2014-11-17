#include "InputHandler.h"


using namespace std;

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::processNormalKeys(unsigned char key, int x, int y) {
	
	float moveScale = 1.0;
	Vector3 lookDir, left, up, vtemp, vtemp2;

	lookDir = Globals::camera->getLookAtPoint() - Globals::camera->getCenterOfProjection();
	up = Globals::camera->getUp();

	left.cross(up, lookDir);
	lookDir.normalize();
	lookDir.scale(moveScale);
	left.normalize();
	left.scale(moveScale);
	up.normalize();
	up.scale(moveScale);

	switch (key) {
		// camera controls
	case 'w':
		vtemp = Globals::camera->getCenterOfProjection() + lookDir;
		vtemp2 = Globals::camera->getLookAtPoint() + lookDir;
		Globals::camera->setCenterOfProjection(vtemp);
		Globals::camera->setLookAtPoint(vtemp2);
		break;
	case 's':
		vtemp = Globals::camera->getCenterOfProjection() - lookDir;
		vtemp2 = Globals::camera->getLookAtPoint() - lookDir;
		Globals::camera->setCenterOfProjection(vtemp);
		Globals::camera->setLookAtPoint(vtemp2);
		break;
	case 'a':
		vtemp = Globals::camera->getCenterOfProjection() + left;
		vtemp2 = Globals::camera->getLookAtPoint() + left;
		Globals::camera->setCenterOfProjection(vtemp);
		Globals::camera->setLookAtPoint(vtemp2);
		break;
	case 'd':
		vtemp = Globals::camera->getCenterOfProjection() - left;
		vtemp2 = Globals::camera->getLookAtPoint() - left;
		Globals::camera->setCenterOfProjection(vtemp);
		Globals::camera->setLookAtPoint(vtemp2);
		break;
	case 'b':	// show/hide bounding spheres
		Globals::showBoundingSpheres = !Globals::showBoundingSpheres;
		break;
	case 'c':	// enable/disable frustum culling
		Globals::cullingEnabled = !Globals::cullingEnabled;
		if (Globals::cullingEnabled) printf("Culling enabled.\n");
		else printf("Culling disabled.\n");
		break;
	case 27: 
		exit(0); 
		break;
	default: return;
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
		//Globals::camera.set(Vector3(0, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
		Globals::cube.setVisible(false);
		Globals::sphere.setVisible(false);
		Globals::house.setVisible(true);
		Globals::bunny.setVisible(false);
		Globals::dragon.setVisible(false);
		
		break;
	case GLUT_KEY_F3:
		//Globals::camera.set(Vector3(-15, 5, 10), Vector3(-5, 0, 0), Vector3(0, 1, 0.5));
		Globals::cube.setVisible(false);
		Globals::sphere.setVisible(false);
		Globals::house.setVisible(true);
		Globals::bunny.setVisible(false);
		Globals::dragon.setVisible(false);
		
		break;
	case GLUT_KEY_F4:
		//Globals::camera.reset();
		Globals::cube.setVisible(false);
		Globals::sphere.setVisible(false);
		Globals::house.setVisible(false);
		Globals::bunny.setVisible(true);
		Globals::dragon.setVisible(false);
		break;
	case GLUT_KEY_F5:
		//Globals::camera.reset();
		Globals::cube.setVisible(false);
		Globals::sphere.setVisible(false);
		Globals::house.setVisible(false);
		Globals::bunny.setVisible(false);
		Globals::dragon.setVisible(true);
		break;
	default:
		break;
	}
}