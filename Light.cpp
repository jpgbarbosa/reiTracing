/* Defines the needed classes and their headers. */
#include "Light.h"

/* In the constructor, we set the centre and the colour of the light point. */
Light::Light(double x, double y, double z, double in, double rC, double gC, double bC):
	intensity(in)
{
    centre.x = x;
    centre.y = y;
    centre.z = z;
    c.r = rC;
    c.g = gC;
    c.b = bC;
}

Light::Light() { }
/* Destructor. */
Light::~Light() {}

/* Returns centre and radius of the sphere. */
point Light::getCentre() { return centre; }
double Light::getIntensity() { return intensity; }

/* Returns the colour of this sphere. */
double Light::getR() {return c.r;}
double Light::getG() {return c.g;}
double Light::getB() {return c.b;}
