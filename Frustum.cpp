#include "Frustum.h"
#include <math.h>


Frustum::Frustum(float _fov, float _aspect, float _near, float _far)
	: fov(_fov), aspect(_aspect), near(_near), far(_far) {

	projection = projectionMatrix(fov, aspect, near, far);
}


Frustum::~Frustum() {
}

Matrix4 Frustum::projectionMatrix(double fov, double aspect, double near, double far) {
	fov = (fov / 180.0) * M_PI;

	// P[0][0]
	double p00 = 1 / (aspect * tan(fov / 2));
	// P[1][1]
	double p11 = 1 / (tan(fov / 2));
	// P[2][2]
	double p22 = (near + far) / (near - far);
	// P[2][3]
	double p23 = (2 * near * far) / (near - far);

	return Matrix4(
		p00, 0, 0, 0,
		0, p11, 0, 0,
		0, 0, p22, p23,
		0, 0, -1, 0);
}

void Frustum::init(Camera* c, Plane* planes) {
	float fovRad = (fov / 180.0) * M_PI;

	float nearH = (near * tan(fovRad / 2.0)) * 2.0;
	float nearW = aspect * nearH;

	Vector3 e = c->getCenterOfProjection();
	Vector3 d = c->getLookAtPoint();
	Vector3 up = c->getUp();

	Vector3 z = e - d;
	z.normalize();

	Vector3 x;
	x.cross(up, z);
	x.normalize();

	Vector3 y;
	y.cross(z, x);

	// calc top-middle point of near plane
	Vector3 yh = y;
	yh.scale(nearH / 2.0);
	// calc right-middle point of near plane
	Vector3 xw = x;
	xw.scale(nearW / 2.0);

	Vector3 zd = z;
	zd.scale(near);
	Vector3 nearCenter = e;
	nearCenter = nearCenter - zd;

	zd = z;
	zd.scale(far);
	Vector3 farCenter = e;
	farCenter = farCenter - zd;

	Vector3 point = nearCenter;
	Vector3 normal = z;
	normal.negate();

	// set near plane
	planes[NEAR].setPoint(point);
	planes[NEAR].setNormal(normal);

	// set far plane
	point = farCenter;
	planes[FAR].setPoint(point);
	normal.negate();
	planes[FAR].setNormal(normal);

	// set top plane
	point = nearCenter;
	point = point + yh; // top-middle point of near
	planes[TOP].setPoint(point);
	point = point - e;
	point.normalize();
	normal.cross(point, x);
	planes[TOP].setNormal(normal);

	// set bottom plane
	point = nearCenter;
	point = point - yh; // bottom-middle point of near
	planes[BOTTOM].setPoint(point);
	point = point - e;
	point.normalize();
	normal.cross(x, point);
	planes[BOTTOM].setNormal(normal);

	// set left plane
	point = nearCenter;
	point = point - xw; // left-middle point of near
	planes[LEFT].setPoint(point);
	point = point - e;
	point.normalize();
	normal.cross(point, y);
	planes[LEFT].setNormal(normal);

	// set right plane
	point = nearCenter;
	point = point + xw; // right-middle point of near
	planes[RIGHT].setPoint(point);
	point = point - e;
	point.normalize();
	normal.cross(y, point);
	planes[RIGHT].setNormal(normal);
}