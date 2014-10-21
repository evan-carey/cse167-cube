#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"

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
	} else if (Globals::sphere.isVisible()) {
		displaySphere();
	} else {
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

// This data structure defines a simple house

int nVerts = 42;    // your vertex array needs to have this many entries

// These are the x,y,z coordinates of the vertices of the triangles
//float vertices[] = {
//	-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
//	-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
//	4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
//	4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
//	4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
//	-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face
//
//	-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
//	-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
//	4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
//	-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
//	4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

// These are the x,y,z coordinates of the vertices of the triangles
Vector3 vertices[] = {
	Vector3(-4, -4, 4), Vector3(4, -4, 4), Vector3(4, 4, 4), Vector3(-4, 4, 4),       // front face
	Vector3(-4, -4, -4), Vector3(-4, -4, 4), Vector3(-4, 4, 4), Vector3(-4, 4, -4),       // left face
	Vector3(4, -4, -4), Vector3(-4, -4, -4), Vector3(-4, 4, -4), Vector3(4, 4, -4),        // back face
	Vector3(4, -4, 4), Vector3(4, -4, -4), Vector3(4, 4, -4), Vector3(4, 4, 4),         // right face
	Vector3(4, 4, 4), Vector3(4, 4, -4), Vector3(-4, 4, -4), Vector3(-4, 4, 4),        // top face
	Vector3(-4, -4, 4), Vector3(-4, -4, -4), Vector3(4, -4, -4), Vector3(4, -4, 4),       // bottom face

	Vector3(-20, -4, 20), Vector3(20, -4, 20), Vector3(20, -4, -20), Vector3(-20, -4, -20), // grass
	Vector3(-4, 4, 4), Vector3(4, 4, 4), Vector3(0, 8, 4),                            // front attic wall
	Vector3(4, 4, 4), Vector3(4, 4, -4), Vector3(0, 8, -4), Vector3(0, 8, 4),      // left slope
	Vector3(-4, 4, 4), Vector3(0, 8, 4), Vector3(0, 8, -4), Vector3(-4, 4, -4),    // right slope
	Vector3(4, 4, -4), Vector3(-4, 4, -4), Vector3(0, 8, -4)                            // rear attic wall
};

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

	0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
	0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
	0, 0, 1, 0, 0, 1, 0, 0, 1 };              // rear attic wall is red

// The index data stores the connectivity of the triangles; 
// index 0 refers to the first triangle defined above
int indices[] = {
	0, 2, 3, 0, 1, 2,      // front face
	4, 6, 7, 4, 5, 6,      // left face
	8, 10, 11, 8, 9, 10,     // back face
	12, 14, 15, 12, 13, 14,   // right face
	16, 18, 19, 16, 17, 18,   // top face
	20, 22, 23, 20, 21, 22,   // bottom face

	24, 26, 27, 24, 25, 26,   // grass
	28, 29, 30,             // front attic wall
	31, 33, 34, 31, 32, 33,   // left slope
	35, 37, 38, 35, 36, 37,   // right slope
	39, 40, 41 };            // rear attic wall


void Window::displayHouse() {

	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	

	// Tell OpenGL what ModelView matrix to use:
	glLoadMatrixd(Globals::camera.getGLMatrix());

	// int numTriangles = sizeof(indices) / sizeof(*indices);

	glBegin(GL_TRIANGLES);

	
		/*for (int i = 0; i < nVerts - 2; i += 3) {
			glColor3d(colors[indices[i] * 3], colors[indices[i] * 3 + 1], colors[indices[i] * 3 + 2]);

			glVertex3f(vertices[indices[i]], vertices[indices[i] + 1], vertices[indices[i] + 2]);

			glVertex3f(vertices[indices[i * 3]], vertices[indices[i * 3] + 1], vertices[indices[i * 3] + 2]);

			glVertex3f(vertices[indices[i * 6]], vertices[indices[i * 6] + 1], vertices[indices[i * 6] + 2]);
		
		}*/
		for (int i = 0; i < 60; i += 3) {
			glColor3d(colors[indices[i] * 3], colors[indices[i] * 3 + 1], colors[indices[i] * 3 + 2]);

			glVertex3f(vertices[indices[i]].getX(), vertices[indices[i]].getY(), vertices[indices[i]].getZ());

			glVertex3f(vertices[indices[i + 1]].getX(), vertices[indices[i + 1]].getY(), vertices[indices[i + 1]].getZ());

			glVertex3f(vertices[indices[i + 2]].getX(), vertices[indices[i + 2]].getY(), vertices[indices[i + 2]].getZ());
		}
	// Set camera
	Vector3 e = Vector3(0.0, 10.0, 10.0);
	Vector3 d = Vector3(0.0, 0.0, 0.0);
	Vector3 up = Vector3(0.0, 1.0, 0.0);

	Globals::camera.setCenterOfProjection(e);
	Globals::camera.setLookAtPoint(d);
	Globals::camera.setUp(up);
	glEnd();

	glFlush();
	glutSwapBuffers();
}