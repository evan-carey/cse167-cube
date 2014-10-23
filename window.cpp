#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "House.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
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
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback() {
	if (Globals::cube.isVisible()) {
		displayCube();
	} 
	if (Globals::sphere.isVisible()) {
		displaySphere();
	} 
	if (Globals::house.isVisible()) {
		displayHouse();
	}
}

void Window::displayCube() {
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

	
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode


	// Tell OpenGL what ModelView matrix to use:
	Matrix4 glmatrix;
	glmatrix = Globals::camera.getCameraMatrix();
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers

	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_TRIANGLES);
		Globals::house.renderHouse();
	glEnd();


	glFlush();
	glutSwapBuffers();
}