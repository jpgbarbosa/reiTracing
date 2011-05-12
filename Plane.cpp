/* Defines the needed classes and their headers. */
#include "Plane.h"
#include "Object.h"
#include "Ray.h"

/* In the constructor, we set the starting point of the ray. */
Plane::Plane(double x, double y, double z, vector n, double rC, double gC, double bC):
    normal(n)
{
    centre.x = x;
    centre.y = y;
    centre.z = z;
    c.r = rC;
    c.g = gC;
    c.b = bC;
}

Plane::Plane() {}
//Destructor
Plane::~Plane() {}


bool Plane::intersects(Ray &ray, double &t)
{
    double numerator = (centre - ray.getOrigin())*normal;
    double denominator = ray.getDir()*normal;

    /* The ray is parallel to the plane. Can be either
     * inside the plane or outside it.
     */
    if (denominator == 0)
        return false;

    t = numerator/denominator;

    /* We are only looking for forward intersections. */
    if (t <= EPSLON)
        return false;
    
    return true;
}

/* Returns the radius of the sphere. */
vector Plane::getNormal() { return normal; }