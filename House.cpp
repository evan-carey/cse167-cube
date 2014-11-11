#include "House.h"
#include "Vector3.h"
#include <GL/glut.h>

void House::renderHouse() {
	int nVerts = 42;    // your vertex array needs to have this many entries

	// These are the x,y,z coordinates of the vertices of the triangles
	Vector3 verticesV[] = {
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


	for (int i = 0; i < 60; i += 3) {
		glColor3f(colors[indices[i] * 3], colors[indices[i] * 3 + 1], colors[indices[i] * 3 + 2]);

		glVertex3f(verticesV[indices[i]].get(0), verticesV[indices[i]].get(1), verticesV[indices[i]].get(2));

		glVertex3f(verticesV[indices[i + 1]].get(0), verticesV[indices[i + 1]].get(1), verticesV[indices[i + 1]].get(2));

		glVertex3f(verticesV[indices[i + 2]].get(0), verticesV[indices[i + 2]].get(1), verticesV[indices[i + 2]].get(2));
	}

	
}


