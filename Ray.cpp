#include <cmath>

/* Defines the needed classes and their headers. */
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"

/* In the constructor, we set the starting point of the ray. */
Ray::Ray(double x, double y, double z, int w, int h):
	wPos(w),
	hPos(h)
{
	origin.x = x;
	origin.y = y;
	origin.z = z;
	intensity = 1;
	
	c.r = 0;
	c.g = 0;
	c.b = 0;

        isToLight = false;
        distanceToLight = 0;
}

//Destructor
Ray::~Ray() {}

void Ray::operator = (Ray& newRay)
{
    /* Make sure it's not the same object. */
    if (this != &newRay)
    {
        /* COPIES: */
        /* The W and H positions...*/
        newRay.setWPos(wPos);
        newRay.setHPos(hPos);

        /* The origin... */
        newRay.setOrigin(origin);

        /* The direction... */
        newRay.setDirection(direction);

        /* The colour...*/
        newRay.setR(c.r);
        newRay.setG(c.g);
        newRay.setB(c.b);

        /* The intensity...*/
        newRay.setIntensity(intensity);
        
    }
    return;
}

/* Sets the direction of the ray. */
void Ray::setDirection(double x, double y, double z)
{
	direction.x = x;
	direction.y = y;
	direction.z = z;
}

void Ray::setDirection(vector v) { direction = v; }

/* Normalizes the direction vector of the ray. */
void Ray::normalize() { direction /= sqrt(direction * direction);}

/* Normalize colour in order to avoid values superior to 1. */
double Ray::normalizeColour()
{
	if (c.r > 1.0)
		c.r = 1.0;
	if (c.g > 1.0)
		c.g = 1.0;
	if (c.b > 1.0)
		c.b = 1.0;
}

/* Returns the corresponding pixel in the final image. */
int Ray::getWPos() { return wPos; }
int Ray::getHPos() { return hPos; }
void Ray::setWPos(int v) { wPos = v; }
void Ray::setHPos(int v) { hPos = v; }

/* Ray coordinates. */
vector Ray::getDir() {return direction;}
point Ray::getOrigin() {return origin;}
void Ray::setOrigin(point p) { origin = p;}

/* Returns the colour for this ray or sets its initial colour. */
double Ray::getR() {return c.r;}
double Ray::getG() {return c.g;}
double Ray::getB() {return c.b;}
void Ray::setR(double v) {c.r = v;}
void Ray::setG(double v) {c.g = v;}
void Ray::setB(double v) {c.b = v;}

/* Updates the colour for this ray. */
void Ray::increaseR(double per) { c.r += per;}
void Ray::increaseG(double per) { c.g += per;}
void Ray::increaseB(double per) { c.b += per;}

double Ray::getIntensity() { return intensity;}
void Ray::multIntensity(double v) {intensity *= v;}
void Ray::setIntensity(double v) {intensity = v;}

void Ray::setIsToLight(bool v, double d) {isToLight = v; distanceToLight = d;}
bool Ray::isToLightRay() {return isToLight;}
double Ray::getToLightDistance() {return distanceToLight;}