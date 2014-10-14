#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <string>

using namespace std;

class Vector4 {
protected:
	double x, y, z, w;
	
public:
	/* Constructor */
	Vector4(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0) : x(x), y(y), z(z), w(w) {}
	
	/* Destructor */
	virtual ~Vector4() {}

	/* Overloaded Operators */
	Vector4 operator+(const Vector4&);
	Vector4 operator-(const Vector4&);
	double operator[](const int index);

	void set(double x0, double y0, double z0, double w0);
	double get(int index) const;

	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }
	double getW() const { return w; }

	double length();

	void dehomogenize(); // dehomogenize the vector (scale it so that its fourth component is equal to one)
	void print(std::string comment = ""); // print x, y, z, and w components of the vector after a comment string
};

#endif