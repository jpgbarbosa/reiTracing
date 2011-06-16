/* Defines the needed classes and their headers. */
#include "Light.h"
#include <cmath>

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

double Light::getFade( double distance)
{
    /* Basically, we give a distance from the light to a limit where the
     * value of the fading will be null, meaning we have a light at all its
     * intensity. From that point one, he decrease it a certain rythm, so
     * the most distant objects won't be as enlighted as the closer ones.
     * Basically, we are produing a fade with a linear decrease from a certain
     * point, defined by FULL_LIGHT_LIMIT.
     */
    if (distance < FULL_LIGHT_LIMIT)
        return 1;
    
    double value = -(distance-FULL_LIGHT_LIMIT)/FADING_COEF + 1;
    
    return value > 1 ? 1 : value;
}
