#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"

class Cube
{
  protected:
    Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
    double angle;                   // rotation angle [degrees]
	double spinAngle;				// spin angle
	bool visible;

	struct COLOR {
		float red;
		float green;
		float blue;
	} color;

  public:
    Cube();   // Constructor

    Matrix4& getMatrix();
	void setMatrix(Matrix4& m);

    void spin(double);      // spin cube [degrees]

	double getAngle();
	void setAngle(double);

	double getSpinAngle();
	void setSpinAngle(double);

	void orbitZ(double);

	void resetPosition();

	float getRed();
	float getGreen();
	float getBlue();

	void setColor(float, float, float);

	bool isVisible();
	void setVisible(bool);
};

#endif

