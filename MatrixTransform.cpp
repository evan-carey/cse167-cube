#include "MatrixTransform.h"


MatrixTransform::MatrixTransform() {
	M.identity();
}

MatrixTransform::MatrixTransform(Matrix4 M) {
	this->M = M;
}


MatrixTransform::~MatrixTransform() {
}

void MatrixTransform::draw(Matrix4 C) {
	Matrix4 tm = C * M;
	for (Node* child : children) {
		//draw(C_new);
		child->draw(tm);
	}
}