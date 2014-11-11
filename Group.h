#pragma once
#include "Node.h"
#include <list>

class Group : public Node {
protected:
	std::list<Node*> children;

public:
	Group(char* n = "");
	virtual ~Group() { children.clear(); }

	void addChild(Node*); // Add child
	void removeChild(Node*); // Remove child
	void removeChild(char* nodeName); // Remove child by name
	void removeChild(int i); // Remove child by index

	void setParent(Node& p) { *this->parent = p; }

	void draw(Matrix4 C);
};

