/* Defines the needed classes and their headers. */
#include <stdio.h>
#include "Triangle.h"
#include "Object.h"
#include "Ray.h"

/* In the constructor, we set the starting point of the ray. */
Triangle::Triangle(double rC, double gC, double bC)
{
    diffuse.r = rC;
    diffuse.g = gC;
    diffuse.b = bC;
}

Triangle::Triangle() {}
//Destructor
Triangle::~Triangle() {}

bool Triangle::intersectsPlane(Ray &ray, double &rT0)
{
    double numerator = (vertixes[0] - ray.getOrigin())*normal;
    double denominator = ray.getDir()*normal;

    /* The ray is parallel to the plane. Can be either
     * inside the plane or outside it.
     */
    if (denominator == 0)
        return false;

    rT0 = numerator/denominator;

    /* We are only looking for forward intersections. */
    if (rT0 <= EPSLON)
        return false;

    return true;
}

void Triangle::crossProduct(point p1, point p2, point p3, point p4, vector &n)
{    
    vector v1 = p1 - p2;
    vector v2 = p3 - p4;
    /* Uses the determinant of the matrix to calculate the normal
     * at this specific vertix.
     */
    n.x = v1.y*v2.z - v1.z*v2.y;
    n.y = -(v1.x*v2.z - v1.z*v2.x);
    n.z = v1.x*v2.y - v1.y*v2.x;

    return;
}

bool Triangle::intersects(Ray &ray, double &rT0, double &rT1)
{
    vector normalAtVertix;
    
    /* First, we have to check if this ray intersects the plane
     * where the triangle is.
     */
    if(!intersectsPlane(ray, rT0))
        return false;

    point x = ray.getOrigin() + rT0*ray.getDir();
    /* Tests for all the vertixes groups. */
    crossProduct(vertixes[1], vertixes[0], x, vertixes[0], normalAtVertix);
    if (normalAtVertix*normal < 0)
        return false;
    
    crossProduct(vertixes[2], vertixes[1], x, vertixes[1], normalAtVertix);
    if (normalAtVertix*normal < 0)
        return false;
    crossProduct(vertixes[0], vertixes[2], x, vertixes[2], normalAtVertix);
    if (normalAtVertix*normal < 0)
        return false;

    return true;
}

void Triangle::newDirection(Ray& ray, double& t)
{
    /* Sets the new origin of the ray. */
    ray.setOrigin(ray.getOrigin() + t*ray.getDir());

    /* And then, its new direction. */
    ray.setDirection(ray.getDir() - 2*(ray.getDir()*normal)*normal);

    ray.normalize();

    return;

}

bool Triangle::refractionRedirection(Ray &ray, double t0, double t1)
{
    if (t0 <= EPSLON)
        return false;

    ray.setOrigin(ray.getOrigin() + t0*ray.getDir());

    return true;
}

void Triangle::intersectionPointNormal(Ray &ray, vector &normalInt)
{
    /* At a plane, the normal at the intersection point is simply the
     * normal of the whole plane.
     */
    normalInt = normal;

    return;
}

/* Returns the radius of the sphere. */
vector Triangle::getNormal() { return normal; }

void Triangle::setNormal() {
    crossProduct(vertixes[2], vertixes[0], vertixes[2], vertixes[1], normal);
    
    /* Normalizes the norm. */
    double length = sqrtf(normal*normal);
    normal /= length;
  
}
void Triangle::setVertix(int vertixNo, double px, double py, double pz)
{
    vertixes[vertixNo].x = px;
    vertixes[vertixNo].y = py;
    vertixes[vertixNo].z = pz;
}