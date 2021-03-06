#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "House.h"
#include "TimeManager.h"
#include "Robot.h"
#include "Frustum.h"

using namespace std;

int Window::width  = 1000;   // set window width in pixels here
int Window::height = 600;   // set window height in pixels here


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback() {
	if (Globals::cube.isVisible()) {
		Globals::cube.spin(Globals::cube.getSpinAngle());   // rotate cube; if it spins too fast try smaller values and vice versa
	}
	if (Globals::sphere.isVisible()) {
		Globals::sphere.spin(Globals::sphere.getSpinAngle());
		Globals::sphere.move();
	}
	displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h) {
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  Globals::frustum->setAspect((double)width / (double)height);
  Matrix4 glmatrix;
  glmatrix = Globals::frustum->getProjectionMatrix();
  glmatrix.transpose();
  //glLoadMatrixd(glmatrix.getPointer());
  gluPerspective(Globals::frustum->getFOV(), Globals::frustum->getAspect(), Globals::frustum->getNear(), Globals::frustum->getFar());
  Globals::frustum->init(Globals::camera, Globals::planes);
  //Globals::frustum->setGLMatrix();
  //gluPerspective(60.0, double(width)/(double)height, 1.0, 50.0); // set perspective projection viewing frustum
  //glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback() {
	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);

	// display fps in console
	TimeManager::Instance().CalculateFrameRate(true);
	
	Globals::frustum->init(Globals::camera, Globals::planes);
	
	displayRobots();

	/*if (Globals::cube.isVisible()) {
		displayCube();
	}
	if (Globals::sphere.isVisible()) {
		displaySphere();
	}
	if (Globals::house.isVisible()) {
		displayHouse();
	}
	if (Globals::bunny.isVisible()) {
		displayBunny();
	}
	if (Globals::dragon.isVisible()) {
		displayDragon();
	}*/
	glFlush();
	glutSwapBuffers();
}


void Window::displayRobots() {
	glColor3f(0.8, 0.8, 0.8);

	for (Robot* robot : Globals::robots) {
		if (robot != NULL)
			robot->draw(Globals::camera->getCInv());
	}
}

void Window::displayCube() {
	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	// Tell OpenGL what ModelView matrix to use:
	Matrix4 glmatrix;
	glmatrix = Globals::cube.getMatrix();
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());
	

	// Draw all six faces of the cube:
	glBegin(GL_QUADS);
	glColor3f(Globals::cube.getRed(), Globals::cube.getGreen(), Globals::cube.getBlue());		// This makes the cube green; the parameters are for red, green and blue. 
	// To change the color of the other faces you will need to repeat this call before each face is drawn.
	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void Window::displaySphere() {
	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	// Tell OpenGL what ModelView matrix to use:
	Matrix4 glmatrix;
	glmatrix = Globals::sphere.getMatrix();
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());

	// Draw all six faces of the cube:
	glBegin(GL_QUADS);
		glColor3f(Globals::sphere.getRed(), Globals::sphere.getGreen(), Globals::sphere.getBlue());	// This makes the sphere red
		// To change the color of the other faces you will need to repeat this call before each face is drawn.
		glutSolidSphere(Globals::sphere.getRadius(), 25.0, 25.0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void Window::displayHouse() {
	glDisable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	// Tell OpenGL what ModelView matrix to use:
	Matrix4 glmatrix;
	glmatrix = Globals::camera->getCameraMatrix();
	glmatrix.print("Camera Matrix:");
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());

	glBegin(GL_TRIANGLES);
		Globals::house.renderHouse();
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void Window::displayBunny() {
	glDisable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	// Use circular pixels
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	// Tell OpenGL what ModelView matrix to use:
	Matrix4 glmatrix;
	glmatrix = Globals::bunny.getMatrix();
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());

	glPointSize(2.0);

	glBegin(GL_POINTS);
		// render bunny model
		for (int i = 0; i < Globals::bunny.length(); ++i) {

			glColor3f(fabs(Globals::bunny.getNorm(i).getx()), fabs(Globals::bunny.getNorm(i).gety()), fabs(Globals::bunny.getNorm(i).getz()));

			glNormal3d(Globals::bunny.getNorm(i).getx(), Globals::bunny.getNorm(i).gety(), Globals::bunny.getNorm(i).getz());
			glVertex3d(Globals::bunny.getPos(i).getx(), Globals::bunny.getPos(i).gety(), Globals::bunny.getPos(i).getz());

		}
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void Window::displayDragon() {
	glDisable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	// use circular pixels
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	// Tell OpenGL what ModelView matrix to use:
	Matrix4 glmatrix;
	glmatrix = Globals::dragon.getMatrix();
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());

	glPointSize(4.0); // enlarge points

	glBegin(GL_POINTS);
		// render dragon model
		for (int i = 0; i < Globals::dragon.length(); ++i) {

			glColor3f(fabs(Globals::dragon.getNorm(i).getx()), fabs(Globals::dragon.getNorm(i).gety()), fabs(Globals::dragon.getNorm(i).getz()));

			glNormal3d(Globals::dragon.getNorm(i).getx(), Globals::dragon.getNorm(i).gety(), Globals::dragon.getNorm(i).getz());
			glVertex3d(Globals::dragon.getPos(i).getx(), Globals::dragon.getPos(i).gety(), Globals::dragon.getPos(i).getz());
		
		}
	glEnd();

	glFlush();
	glutSwapBuffers();
}