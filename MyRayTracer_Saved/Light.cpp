#include "Light.h"

/* In the constructor, we set the starting point of the ray. */
Light::Light(double x, double y, double z, double in, double rC, double gC, double bC):
	cX(x),
	cY(y),
	cZ(z),
	intensity(in),
	/* Remember, these are percentages of reflection. */
	r(rC),
	g(gC),
	b(bC)
{
	
}

//Destructor
Light::~Light() {}

/* Returns centre and radius of the sphere. */
double Light::getX() { return cX; }
double Light::getY() { return cY; }
double Light::getZ() { return cZ; }
double Light::getIntensity() { return intensity; }


/* Returns the colour of this sphere. */
double Light::getR() {return r;}
double Light::getG() {return g;}
double Light::getB() {return b;}
