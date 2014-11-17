#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>
#include "Window.h"
#include "Matrix4.h"
#include "main.h"
#include "InputHandler.h"
#include <time.h>

using namespace std;


namespace Globals {
	Cube cube;
	Sphere sphere;
	Camera* camera;
	House house;
	PointCloud bunny;
	PointCloud dragon;
	std::vector<Robot*> robots;
	double currentRotationAngle;
	bool showBoundingSpheres = false;
	bool cullingEnabled = true;
	Frustum* frustum;
	Plane* planes;
};

int main(int argc, char *argv[]) {

	srand(time(NULL));

  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("CSE167 - Evan Carey");    	      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);	// normalize vectors to unit length after transformation,
							// preventing the white lighting bug caused by scaling
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

  // Initialize input handler
  glutKeyboardFunc(InputHandler::processNormalKeys);
  glutSpecialFunc(InputHandler::processSpecialKeys);
    
  // Initialize cube matrix:
  //Globals::cube.getMatrix().identity();

  // Initialize sphere matrix
  //Globals::sphere.getMatrix().identity();

  // Initialize bunny
  //printf("\n-----Bunny-------------------------------\n");
  //Globals::bunny.createFromFile("res/bunny.xyz");
  //printf("-----------------------------------------\n");

  // Initialize dragon
  //printf("\n-----Dragon------------------------------\n");
  //Globals::dragon.createFromFile("res/dragon.xyz");
  //printf("-----------------------------------------\n");
  
  
  // Print position
  //Globals::cube.getMatrix().print("Initial Matrix: ");

  // Initialize camera
  Globals::camera = new Camera();
  Globals::camera->set(Vector3(3, 5, 5), Vector3(-5, 0, -5), Vector3(0, 1, 0));
  //Globals::camera->set(Vector3(0, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
  //Globals::camera->translate(0, 0, -20);

  // Initialize frustum
  Globals::frustum = new Frustum(60.0, (double)Window::width / (double)Window::height, 1.0, 1000.0);
  Globals::planes = new Plane[6];
  // Initialize robots
  Matrix4 c;
  c.identity();

  Matrix4 offset;
  offset.identity();
  offset.makeTranslate(0, 0, 4);

  for (int i = 0; i < (int)(sqrt(NUM_ROBOTS)); ++i) {
	  for (int j = 0; j < (int)(sqrt(NUM_ROBOTS)); ++j) {
		  offset.identity();
		  offset.makeTranslate(-i * 3, 0.0, -j * 3);
		  Globals::robots.push_back(new Robot(offset));
		  //printf("%d\n", i * j + j);
	  }
  }

  glutMainLoop();
  return 0;
}

