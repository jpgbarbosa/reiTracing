#include <cmath>
#include <stdio.h>
#include "Ray.h"
#include "Object.h"
#include "Sphere.h"

/* In the constructor, we set the starting point of the ray. */
Ray::Ray(double x, double y, double z, int w, int h):
	wPos(w),
	hPos(h)
{
	origin.x = x;
	origin.y = y;
	origin.z = z;
	intensity = 1;
	
	r = 0;
	g = 0;
	b = 0;
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

void Ray::setDirection(vector &v)
{
	direction = v;
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
	normal = origin + t*direction - sphere.getCentre();
	
	/* Now, we update the start of the ray, which
	 * is the intersection point.
	 */
	origin = origin + t*direction;	
	
	/* Then, calculates the normal. */
	double length = sqrtf(normal*normal);
	normal /= length;
	
	/* With the normal calculated, we find the new direction
	 * vector.
	 * r = d - 2(n.d)n
	 * Where d is the old direction and n is the normal.
	 * TODO: That outter n is inner or external product?
	 */
	direction = direction - 2*(direction*normal)*normal;

	return;
}

/* Normalize colour in order to avoid values superior to 1. */
double Ray::normalizeColour()
{
	if (r > 1.0)
		r = 1.0;
	if (g > 1.0)
		g = 1.0;
	if (b > 1.0)
		b = 1.0;
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

/* Updates the colour for this ray. */
void Ray::increaseR(double per) { r += per;}
void Ray::increaseG(double per) { g += per;}
void Ray::increaseB(double per) { b += per;}

double Ray::getIntensity() { return intensity;}
void Ray::multIntensity(double v) {intensity *= v;}