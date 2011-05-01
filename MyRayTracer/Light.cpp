#include "Light.h"

/* In the constructor, we set the starting point of the ray. */
Light::Light(double x, double y, double z, double in, double rC, double gC, double bC):
	intensity(in),
	/* Remember, these are percentages of reflection. */
	r(rC),
	g(gC),
	b(bC)
{
	centre.x = x;
    centre.y = y;
	centre.z = z;
}

//Destructor
Light::~Light() {}

/* Returns centre and radius of the sphere. */
point Light::getCentre() { return centre; }
double Light::getIntensity() { return intensity; }


/* Returns the colour of this sphere. */
double Light::getR() {return r;}
double Light::getG() {return g;}
double Light::getB() {return b;}
