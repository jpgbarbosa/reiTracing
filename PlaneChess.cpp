/* Defines the needed classes and their headers. */
#include "PlaneChess.h"
#include "Object.h"
#include "Ray.h"
#include <iostream>

/* In the constructor, we set the starting point of the ray. */
PlaneChess::PlaneChess(double x, double y, double z, vector n, double sS):
    normal(n)
{
    centre.x = x;
    centre.y = y;
    centre.z = z;

    squareSize = sS;
}

PlaneChess::PlaneChess() {}
//Destructor
PlaneChess::~PlaneChess() {}


bool PlaneChess::intersects(Ray &ray, double &rT0, double &rT1)
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

    /* As this is a chess plane, we have to first check which colour
     * should be this one.
     */
    point iP = ray.getOrigin() + rT0*ray.getDir();

    int xTemp = int(floor(iP.x / squareSize));
    int zTemp = int (floor(iP.z / squareSize));

   //std::cout << "We have " << xTemp << " and " << zTemp << std::endl;
    /* Now, depending on the position it hits, draw a white or black square. */
    if ((xTemp & 1) == 0)
    {
        if ((zTemp & 1) == 0)
        {
            c.r = 1;
            c.g = 1;
            c.b = 1;
            diffuse.r = 1;
            diffuse.g = 1;
            diffuse.b = 1;
        }
        else
        {
            c.r = 0;
            c.g = 0;
            c.b = 0;
            diffuse.r = 0;
            diffuse.g = 0;
            diffuse.b = 0;
        }
    }
    else
    {
      if ((zTemp & 1) == 0)
        {
            c.r = 0;
            c.g = 0;
            c.b = 0;
            diffuse.r = 0;
            diffuse.g = 0;
            diffuse.b = 0;
        }
        else
        {
            c.r = 1;
            c.g = 1;
            c.b = 1;
            diffuse.r = 1;
            diffuse.g = 1;
            diffuse.b = 1;
        }
    }
    
    return true;
}

void PlaneChess::newDirection(Ray &ray, double &t)
{
    /* Sets the new origin of the ray. */
    ray.setOrigin(ray.getOrigin() + t*ray.getDir());

    /* And then, its new direction. */
    ray.setDirection(ray.getDir() - 2*(ray.getDir()*normal)*normal);

    ray.normalize();

    return;

}

/* In a plane, with no thickness, the ray will continue to move. Therefore, the
 * starting point of the ray will be the same as the intersection point and the
 * direction of the ray won't change.
 */
bool PlaneChess::refractionRedirection(Ray &ray, double t0, double t1)
{
    if (t0 <= EPSLON)
        return false;
    
    ray.setOrigin(ray.getOrigin() + t0*ray.getDir());
    
    return true;
}

void PlaneChess::intersectionPointNormal(Ray &ray, vector &normalInt)
{
    /* At a plane, the normal at the intersection point is simply the
     * normal of the whole plane.
     */
    normalInt = normal;

    return;
}

/* Returns the radius of the sphere. */
vector PlaneChess::getNormal() { return normal; }