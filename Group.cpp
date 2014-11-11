#include "Group.h"

Group::Group(char* n) {
	this->name = n;
	children = std::list<Node*>();
}


void Group::addChild(Node* child) {
	children.push_back(child);
}

void Group::removeChild(Node* child) {
	children.remove(child);
}

void Group::removeChild(char* childName) {
	for (Node* child : children) {
		if (strcmp(childName, child->getName())) {
			children.remove(child);
		}
	}
}

void Group::removeChild(int index) {
	std::list<Node*>::iterator it = children.begin();
	std::advance(it, index);
	children.erase(it);
}

void Group::draw(Matrix4 C) {
	for (Node* child : children) {
		child->draw(C);
		// draw(C);
	}
}
