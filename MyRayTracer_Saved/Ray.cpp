#include <cmath>
#include "Ray.h"

/* In the constructor, we set the starting point of the ray. */
Ray::Ray(double x, double y, double z, int w, int h):
	initX(x),
	initY(y),
	initZ(z),
	wPos(w),
	hPos(h)
{
	
}

//Destructor
Ray::~Ray() {}

/* Sets the direction of the ray. */
void Ray::setDirection(double x, double y, double z)
{
	xDir = x;
	yDir = y;
	zDir = z;
	
	return;
}

/* Normalizes the direction vector of the ray. */
void Ray::normalize()
{
	double length = sqrt((xDir*xDir) + (yDir*yDir) + (zDir*zDir));
	xDir /= length;
	yDir /= length;
	zDir /= length;
	
	return;
}

/* Sets the new direction of the ray after an intersection.
 * See more at:
 * http://en.wikipedia.org/wiki/Ray_tracing_(graphics)
 */
void Ray::newDirection(double t, Sphere &sphere)
{
	double normal[3];
	
	/* First, we calculate the normal.
	 * n = (y - c) / ||y - c||
	 * Where y is the intersection point and c the centre
	 * of the sphere.
	 */
	normal[0] = initX + t*initX - sphere.getX();
	normal[1] = initY + t*initY - sphere.getY();
	normal[2] = initZ + t*initZ - sphere.getZ();
	
	/* Then, calculates the normal. */
	double length = sqrt((normal[0]*normal[0])
					+ (normal[1]*normal[1])
						+ (normal[2]*normal[2]));
	normal[0] /= length;
	normal[1] /= length;
	normal[2] /= length;
	
	/* With the normal calculated, we find the new direction
	 * vector.
	 * r = d - 2(n.d)n
	 * Where d is the old direction and n is the normal.
	 * TODO: That outter n is inner or external product?
	 */
	xDir = xDir - 2*(xDir*normal[0])*xDir;
	yDir = yDir - 2*(yDir*normal[1])*yDir;
	zDir = zDir - 2*(zDir*normal[2])*zDir;
	
	/* Now, we update the start of the ray, which
	 * is the intersection point.
	 */
	initX += t*initX;
	initY += t*initY;
	initZ += t*initZ;
	
	return;
}

/* Returns the corresponding pixel in the final image. */
int Ray::getWPos() { return wPos; }
int Ray::getHPos() { return hPos; }
/* Ray coordinates. */
double Ray::getXDir() {return xDir;}
double Ray::getYDir() {return yDir;}
double Ray::getZDir() {return zDir;}
double Ray::getInitX() {return initX;}
double Ray::getInitY() {return initY;}
double Ray::getInitZ() {return initZ;}
void Ray::setXDir(double v) { xDir = v;}
void Ray::setYDir(double v) { yDir = v;}
void Ray::setZDir(double v) { zDir = v;}
void Ray::setInitX(double v) { initX = v;}
void Ray::setInitY(double v) { initY = v;}
void Ray::setInitZ(double v) { initZ = v;}

/* Returns the colour for this ray or sets its initial colour. */
double Ray::getR() {return r;}
double Ray::getG() {return g;}
double Ray::getB() {return b;}
void Ray::setColour(double rC, double gC, double bC) { r = rC; g = gC; b = bC;}

/* Updates the colour for this ray. */
void Ray::updateR(double per) { r *= per;};
void Ray::updateG(double per) { g *= per;};
void Ray::updateB(double per) { b *= per;};