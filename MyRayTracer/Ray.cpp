#include <cmath>
#include "Ray.h"

/* In the constructor, we set the starting point of the ray. */
Ray::Ray(double x, double y, double z, int w, int h):
	wPos(w),
	hPos(h)
{
	origin.x = x;
	origin.y = y;
	origin.z = z;
}

//Destructor
Ray::~Ray() {}

/* Sets the direction of the ray. */
void Ray::setDirection(double x, double y, double z)
{
	direction.x = x;
	direction.y = y;
	direction.z = z;
}

/* Normalizes the direction vector of the ray. */
void Ray::normalize()
{
	double length = sqrt((direction.x*direction.x)
						+ (direction.y*direction.y)
							+ (direction.z*direction.z));
	direction.x /= length;
	direction.y /= length;
	direction.z /= length;
}

/* Sets the new direction of the ray after an intersection.
 * See more at:
 * http://en.wikipedia.org/wiki/Ray_tracing_(graphics)
 */
void Ray::newDirection(double t, Sphere &sphere)
{
	vector normal;
	
	/* First, we calculate the normal.
	 * n = (y - c) / ||y - c||
	 * Where y is the intersection point and c the centre
	 * of the sphere.
	 */
	normal.x = origin.x + t*origin.x - sphere.getCentre().x;
	normal.y = origin.y + t*origin.y - sphere.getCentre().y;
	normal.z = origin.y + t*origin.z - sphere.getCentre().z;
	
	/* Then, calculates the normal. */
	double length = sqrt((normal.x*normal.x)
					+ (normal.y*normal.y)
						+ (normal.z*normal.z));
	normal /= length;
	
	/* With the normal calculated, we find the new direction
	 * vector.
	 * r = d - 2(n.d)n
	 * Where d is the old direction and n is the normal.
	 * TODO: That outter n is inner or external product?
	 */
	direction += -2*(direction*normal)*direction;
	
	/* Now, we update the start of the ray, which
	 * is the intersection point.
	 */
	origin += t*origin;
	
	return;
}

/* Returns the corresponding pixel in the final image. */
int Ray::getWPos() { return wPos; }
int Ray::getHPos() { return hPos; }
/* Ray coordinates. */
vector Ray::getDir() {return direction;}
point Ray::getOrigin() {return origin;}
void Ray::setOrigin(point &p) { origin = p;}

/* Returns the colour for this ray or sets its initial colour. */
double Ray::getR() {return r;}
double Ray::getG() {return g;}
double Ray::getB() {return b;}
void Ray::setColour(double rC, double gC, double bC) { r = rC; g = gC; b = bC;}

/* Updates the colour for this ray. */
void Ray::updateR(double per) { r *= per;};
void Ray::updateG(double per) { g *= per;};
void Ray::updateB(double per) { b *= per;};