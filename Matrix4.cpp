#include <math.h>

#include "Matrix4.h"

using namespace std;

/**
 * Constructors
 */
Matrix4::Matrix4() {
	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			m[i][j] = 0.0;
		}
	}
}

Matrix4::Matrix4(double m0, double m1, double m2, double m3, 
				 double m4, double m5, double m6, double m7,
				 double m8, double m9, double m10, double m11,
				 double m12, double m13, double m14, double m15) {

	m[0][0] = m0;	m[0][1] = m1;	m[0][2] = m2;	m[0][3] = m3;
	m[1][0] = m4;	m[1][1] = m5;	m[1][2] = m6;	m[1][3] = m7;
	m[2][0] = m8;	m[2][1] = m9;	m[2][2] = m10;	m[2][3] = m11;
	m[3][0] = m12;	m[3][1] = m13;	m[3][2] = m14;	m[3][3] = m15;
}

Matrix4::Matrix4(Matrix4& other) {
	m[0][0] = other.m[0][0];	m[0][1] = other.m[0][1];	m[0][2] = other.m[0][2];	m[0][3] = other.m[0][3];
	m[1][0] = other.m[1][0];	m[1][1] = other.m[1][1];	m[1][2] = other.m[1][2];	m[1][3] = other.m[1][3];
	m[2][0] = other.m[2][0];	m[2][1] = other.m[2][1];	m[2][2] = other.m[2][2];	m[2][3] = other.m[2][3];
	m[3][0] = other.m[3][0];	m[3][1] = other.m[3][1];	m[3][2] = other.m[3][2];	m[3][3] = other.m[3][3];
}

/**
 * Overloaded operators
 */
Matrix4& Matrix4::operator=(const Matrix4& m2) {
	if (this != &m2) {
		for (int i=0; i<4; ++i) {
			for (int j=0; j<4; ++j) {
				m[i][j] = m2.m[i][j];
			}
		}
	}
	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& m2) {
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			double sum = 0.0;
			for (int k = 0; k < 4; k++) {
				sum += (m[i][k] * m2.get(k, j));
			}
			m[i][j] = sum;
		}
	}
	
	
	/*
	m[0][0] = m[0][0] * m2.get(0, 0) + m[0][1] * m2.get(1, 0) + m[0][2] * m2.get(2, 0) + m[0][3] * m2.get(3, 0);
	m[1][0] = m[1][0] * m2.get(0, 0) + m[1][1] * m2.get(1, 0) + m[1][2] * m2.get(2, 0) + m[1][3] * m2.get(3, 0);
	m[2][0] = m[2][0] * m2.get(0, 0) + m[2][1] * m2.get(1, 0) + m[2][2] * m2.get(2, 0) + m[2][3] * m2.get(3, 0);
	m[3][0] = m[3][0] * m2.get(0, 0) + m[3][1] * m2.get(1, 0) + m[3][2] * m2.get(2, 0) + m[3][3] * m2.get(3, 0);

	m[0][1] = m[0][0] * m2.get(0, 1) + m[0][1] * m2.get(1, 1) + m[0][2] * m2.get(2, 1) + m[0][3] * m2.get(3, 1);
	m[1][1] = m[1][0] * m2.get(0, 1) + m[1][1] * m2.get(1, 1) + m[1][2] * m2.get(2, 1) + m[1][3] * m2.get(3, 1);
	m[2][1] = m[2][0] * m2.get(0, 1) + m[2][1] * m2.get(1, 1) + m[2][2] * m2.get(2, 1) + m[2][3] * m2.get(3, 1);
	m[3][1] = m[3][0] * m2.get(0, 1) + m[3][1] * m2.get(1, 1) + m[3][2] * m2.get(2, 1) + m[3][3] * m2.get(3, 1);
	*/

	return *this;
}

Matrix4 Matrix4::operator*=(const Matrix4& m2) {
	*this = *this * m2;
	return *this;
}

Matrix4* Matrix4::multiply(Matrix4& m2) {
	double n[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			n[i][j] = 0.0;
			for (int k = 0; k < 4; k++) {
				n[i][j] += m[i][k] * m2.get(k, j);
			}
		}
	}
	return &Matrix4(n[0][0], n[0][1], n[0][2], n[0][3],
					n[1][0], n[1][1], n[1][2], n[1][3],
					n[2][0], n[2][1], n[2][2], n[2][3],
					n[3][0], n[3][1], n[3][2], n[3][3]);
}



Vector4 Matrix4::operator*(const Vector4& v) {	

	double x = m[0][0] * v.getX() + m[0][1] * v.getY() + m[0][2] * v.getZ() + m[0][3] * v.getW();
	double y = m[1][0] * v.getX() + m[1][1] * v.getY() + m[1][2] * v.getZ() + m[1][3] * v.getW();
	double z = m[2][0] * v.getX() + m[2][1] * v.getY() + m[2][2] * v.getZ() + m[2][3] * v.getW();
	double w = m[3][0] * v.getX() + m[3][1] * v.getY() + m[3][2] * v.getZ() + m[3][3] * v.getW();

	return Vector4(x, y, z, w);

	/*double n[4];
	double temp_sum;
	for (int i = 0; i < 4; i++) {
		temp_sum = 0.0;
		for (int j = 0; j < 4; j++) {
			temp_sum += m[i][j] * v.get(j);
		}
		n[i] = temp_sum;
	}
	return Vector4(n[0], n[1], n[2], n[3]);*/
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}


void Matrix4::set(int pos, double val) {
	if (pos < 0 || pos > 15) return;
	int i = pos << 2;
	int j = pos % 4;
	m[i][j] = val;
}

void Matrix4::set(int row, int col, double val) {
	if (row < 0 || row > 3 || col < 0 || col > 3) return;
	m[row][col] = val;
}

double Matrix4::get(int pos) const {
	if (pos < 0 || pos > 15) return 0.0;
	int i = pos << 2;
	int j = pos % 4;
	return m[i][j];
}

double Matrix4::get(int row, int col) const {
	if (row < 0 || row > 3 || col < 0 || col > 3) return 0.0;
	return m[row][col];
}

// set matrix to identity matrix
void Matrix4::identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) m[i][j] = 1.0;
			else		m[i][j] = 0.0;
		}
	}
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose() {
	Matrix4 temp;
	for (int i=0; i<4; ++i) {
	    for (int j=0; j<4; ++j) {
			temp.m[j][i] = m[i][j];
		}
	}
	*this = temp;  // copy temporary values to this matrix
}

// Creates a rotation matrix which rotates about the x axis.
// angle is expected in degrees
void Matrix4::makeRotateX(double angle) {
	angle = (angle / 180.0) * M_PI;

	Matrix4 rm = Matrix4(0.0, 0.0, 0.0, 0.0,
						0.0, cos(angle), -sin(angle), 0.0,
						0.0, sin(angle), cos(angle), 0.0,
						0.0, 0.0, 0.0, 1.0);

	*this *= rm;
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle) {
	angle = (angle / 180.0) * M_PI;  // convert from degrees to radians

	Matrix4 rm = Matrix4(cos(angle), 0.0, sin(angle), 0.0,
						0.0, 1.0, 0.0, 0.0,
						-sin(angle), 0.0, cos(angle), 0.0,
						0.0, 0.0, 0.0, 1.0);

	//*this *= rm;

	Matrix4 *res = this->multiply(rm);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = res->get(i, j);
		}
	}
	

	/*double c = cos(angle);
	double s = sin(angle);
	m[0][0] = m[0][0] * c + m[2][0] * s;
	m[2][0] = m[0][0] * -s + m[2][0] * c;
	m[0][1] = m[0][1] * c + m[2][1] * s;
	m[2][1] = m[0][1] * -s + m[2][1] * c;
	m[0][2] = m[0][2] * c + m[2][2] * s;
	m[2][2] = m[0][2] * -s + m[2][2] * c;
	m[0][3] = m[0][3] * c + m[2][3] * s;
	m[2][3] = m[0][3] * -s + m[2][3] * c;*/
}

// Creates a rotation matrix which rotates about the z axis.
// angle is expected in degrees
void Matrix4::makeRotateZ(double angle) {
	angle = angle / 180.0 * M_PI;

	/*m[0][0] = cos(angle);	m[0][1] = -sin(angle);	m[0][2] = 0.0;	m[0][3] = 0.0;
	m[1][0] = sin(angle);	m[1][1] = cos(angle);	m[1][2] = 0.0;	m[1][3] = 0.0;
	m[2][0] = 0.0;			m[2][1] = 0.0;			m[2][2] = 1.0;	m[2][3] = 0.0;
	m[3][0] = 0.0;			m[3][1] = 0.0;			m[3][2] = 0.0;	m[3][3] = 1.0;*/

	Matrix4 rm = Matrix4(cos(angle), -sin(angle), 0.0, 0.0,
						sin(angle), cos(angle), 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);

	*this *= rm;

	/*
	Matrix4 *res = this->multiply(rm);
	//Matrix4 *res = rm.multiply(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = res->get(i, j);
		}
	}
	*/
}

void Matrix4::makeOrbitZ(double angle) {
	angle = angle / 180.0 * M_PI;

	/*
	m[0][0] = cos(angle);	m[0][1] = -sin(angle);	m[0][2] = 0.0;	m[0][3] = 0.0;
	m[1][0] = sin(angle);	m[1][1] = cos(angle);	m[1][2] = 0.0;	m[1][3] = 0.0;
	m[2][0] = 0.0;			m[2][1] = 0.0;			m[2][2] = 1.0;	m[2][3] = 0.0;
	m[3][0] = 0.0;			m[3][1] = 0.0;			m[3][2] = 0.0;	m[3][3] = 1.0;
	*/

	Matrix4 rm = Matrix4(cos(angle), -sin(angle), 0.0, 0.0,
						sin(angle), cos(angle), 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);

	//*this *= rm;
	//*this = rm * *this;
	//Matrix4 *res = this->multiply(rm);
	Matrix4 *res = rm.multiply(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = res->get(i, j);
		}
	}
}

void Matrix4::makeRotate(double angle, const Vector3& axis) {
	Vector3 a;
	double ax = axis.getX();
	double ay = axis.getY();
	double az = axis.getZ();
	a.set(ax, ay, az);
	a.normalize();

	angle = angle / 180.0 * M_PI;
	double c = cos(angle);
	double s = sin(angle);

	// rotation matrix
	m[0][0] = c + ax*ax*(1 - c);	m[0][1] = ax*ay*(1 - c) - az*s;	m[0][2] = ax*az*(1 - c) + ay*s;	m[0][3] = 0.0;
	m[1][0] = ay*ax*(1 - c) + az*s;	m[1][1] = c + ax*ax*(1 - c);	m[1][2] = ay*az*(1 - c) - ax*s;	m[1][3] = 0.0;
	m[2][0] = az*ax*(1 - c) + ay*s;	m[2][1] = az*ay*(1 - c) + ax*s;	m[2][2] = c + az*az*(1 - c);	m[2][3] = 0.0;
	m[3][0] = 0.0;					m[3][1] = 0.0;					m[3][2] = 0.0;					m[3][3] = 1.0;

}

void Matrix4::makeScale(double sx, double sy, double sz) {
	
	Matrix4 sm = Matrix4(sx, 0.0, 0.0, 0.0, 
						0.0, sy, 0.0, 0.0, 
						0.0, 0.0, sz, 0.0, 
						0.0, 0.0, 0.0, 1.0);

	*this *= sm;
	/*
	Matrix4* res = this->multiply(sm);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = res->get(i, j);
		}
	}
	*/
	

	/*
	m[0][0] *= sx;	m[0][1] *= 0.0;	m[0][2] *= 0.0;	m[0][3] *= 0.0;
	m[1][0] *= 0.0;	m[1][1] *= sy;	m[1][2] *= 0.0;	m[1][3] *= 0.0;
	m[2][0] *= 0.0;	m[2][1] *= 0.0;	m[2][2] *= sz;	m[2][3] *= 0.0;
	m[3][0] = 0.0;	m[3][1] = 0.0;	m[3][2] = 0.0;	m[3][3] = 1.0;
	*/
	
	/*m[0][0] *= sx;	m[0][1] *= sx;	m[0][2] *= sx;	m[0][3] *= sx;
	m[1][0] *= sy;	m[1][1] *= sy;	m[1][2] *= sy;	m[1][3] *= sy;
	m[2][0] *= sz;	m[2][1] *= sz;	m[2][2] *= sz;	m[2][3] *= sz;
	*/
}

void Matrix4::makeTranslate(double tx, double ty, double tz) {
	
	Matrix4 tm(1.0, 0.0, 0.0, tx, 
			   0.0, 1.0, 0.0, ty, 
			   0.0, 0.0, 1.0, tz, 
			   0.0, 0.0, 0.0, 1.0);

	
	Matrix4 *res = tm.multiply(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = res->get(i, j);
		}
	}
	
	
	//*this = *this * translationMatrix;
	//(*this * translationMatrix).transpose();
	//transpose();
	
	//m[3][0] = tx + m[3][0];
	//m[3][1] = ty + m[3][1];
	//m[3][2] = tz + m[3][2];
	
	//m[0][3] += tx;
	//m[1][3] += ty;
	//m[2][3] += tz;

	/*
	m[0][0] += m[3][0] * tx;	m[0][1] += m[3][1] * tx;	m[0][2] += m[3][2] * tx;	m[0][3] += m[3][3] * tx;
	m[1][0] += m[3][0] * ty;	m[1][1] += m[3][1] * ty;	m[1][2] += m[3][2] * ty;	m[1][3] += m[3][3] * ty;
	m[2][0] += m[3][0] * tz;	m[2][1] += m[3][1] * tz;	m[2][2] += m[3][2] * tz;	m[2][3] += m[3][3] * tz;
	*/
	//transpose();
}

void Matrix4::print(std::string comment) {
	std::cout << comment << "\n";
	for (int i = 0; i < 4; i++) {
		std::cout << "[ ";
		for (int j = 0; j < 4; j++) {
			if (j < 3) printf("%.2f,\t", m[i][j]);
			else	   printf("%.2f ]\n", m[i][j]);
		}
	}
	std::cout << "\n";
}