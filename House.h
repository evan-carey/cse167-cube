#pragma once
#include "Matrix4.h"

class House {
protected:
	bool visible;
	Matrix4 model2world;
public:
	House() {
		visible = false;
		model2world = Matrix4(); 
		model2world.identity(); 
	}
	virtual ~House() {}

	void setVisible(bool v) { visible = v; }
	bool isVisible() { return visible; }

	Matrix4& getMatrix() { return model2world; }
	void renderHouse();
};

