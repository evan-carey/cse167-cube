#pragma once

#include "Matrix4.h"

class Node {
protected:
	char* name;
	Node* parent;
public:
	Node();
	virtual ~Node();

	char* getName() { return name; }
	void setName(char* n) { this->name = n; }

	virtual void draw(Matrix4 C) = 0;

	bool operator==(Node& n) const { return strcmp(this->name, n.name) == 0; }
};

