#include "ObjReader.h"
#include <iostream>

ObjReader::ObjReader() {
}


ObjReader::~ObjReader() {
}

void ObjReader::readObj(char* fileName, vector<Point3D>& position, vector<Point3D>& normal) {
	
	// position coordinates
	float posX = 0.0, posY = 0.0, posZ = 0.0;
	// normal coordinates
	float normX = 0.0, normY = 0.0, normZ = 0.0;
	
	FILE* fp;

	// open file for reading
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Error reading from file \"%s\". Please ensure it exists and try again.\n", fileName);
		cin.get();
		exit(1);
	}
	while (fscanf(fp, "%f %f %f %f %f %f", &posX, &posY, &posZ, &normX, &normY, &normZ) != EOF) {
		position.push_back(Point3D((double)posX, (double)posY, (double)posZ));
		normal.push_back(Point3D((double)normX, (double)normY, (double)normZ));
	}
	
	// close file
	fclose(fp);
}