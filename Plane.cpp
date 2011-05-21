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
    intersectionType = INTERSECTS_PLANE;
}

Plane::Plane() {}
//Destructor
Plane::~Plane() {}


bool Plane::intersects(Ray &ray, double &rT0, double &rT1)
{
    double numerator = (centre - ray.getOrigin())*normal;
    double denominator = ray.getDir()*normal;

    /* The ray is parallel to the plane. Can be either
     * inside the plane or outside it.
     */
    if (denominator == 0)
        return false;

    rT0 = numerator/denominator;
    /* Just to make sure we invalidate rT1. */
    rT1 = EPSLON;

    /* We are only looking for forward intersections. */
    if (rT0 <= EPSLON)
        return false;

    /* We have to check if intersection point is beyond the light
     * or not.
     */
    if (ray.isToLightRay())
        if (rT0 > ray.getToLightDistance())
            return false;

    return true;
}

void Plane::newDirection(Ray &ray, double &t)
{
    /* Sets the new origin of the ray. */
    ray.setOrigin(ray.getOrigin() + t*ray.getDir());

    /* And then, its new direction. */
    ray.setDirection(2*(ray.getDir()*normal)*normal - ray.getDir());

    ray.normalize();

    return;

}

/* In a plane, with no thickness, the ray will continue to move. Therefore, the
 * starting point of the ray will be the same as the intersection point and the
 * direction of the ray won't change.
 */
bool Plane::refractionRedirection(Ray &ray, double t0, double t1)
{
    if (t0 <= EPSLON)
        return false;
    
    ray.setOrigin(ray.getOrigin() + t0*ray.getDir());
    
    return true;
}

void Plane::intersectionPointNormal(Ray &ray, vector &normalInt)
{
    /* At a plane, the normal at the intersection point is simply the
     * normal of the whole plane.
     */
    normalInt = normal;

    return;
}

/* Returns the radius of the sphere. */
vector Plane::getNormal() { return normal; }