/* Defines the needed classes and their headers. */
#include <stdio.h>
#include "Sphere.h"
#include "Object.h"
#include "Ray.h"

/* In the constructor, we set the starting point of the ray. */
Sphere::Sphere(double x, double y, double z, double rad, double rC, double gC, double bC):
	radius(rad)
{
    centre.x = x;
    centre.y = y;
    centre.z = z;
    c.r = rC;
    c.g = gC;
    c.b = bC;
    intersectionType = INTERSECTS_SPHERE;
    
}

Sphere::Sphere() {}
//Destructor
Sphere::~Sphere() {}

/* See more at:
 * http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection
 * http://paulbourke.net/geometry/sphereline/
 * http://www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm
 *
 * OTHER INTERSECTIONS:
 * http://flylib.com/books/en/2.124.1.137/1/
 */ 
bool Sphere::intersects(Ray &ray, double &rT0, double &rT1)
{
    /* Compute a, b and c coefficients. */
	//a = (x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2
    double a = ray.getDir()*ray.getDir();
	//b = 2[ (x2 - x1) (x1 - x3) + (y2 - y1) (y1 - y3) + (z2 - z1) (z1 - z3) ]
	double b = 2*(ray.getDir()*(ray.getOrigin() - centre));
	//c = x3^2 + y3^2 + z3^2 + x1^2 + y1^2 + z1^2 - 2[x3.x1 + y3.y1 + z3.z1] - r^2
    double c = centre*centre + ray.getOrigin()*ray.getOrigin() - 2*(ray.getOrigin()*centre) - radius*radius;

    /* Find the discriminant. */
    double disc = b * b - 4 * a * c;
    
    /* If discriminant is negative there are no real roots, so return 
     * false as ray misses sphere.
	 */
    if (disc < 0)
        return false;

    /* Compute q as described in the first link. */
    double distSqrt = sqrtf(disc);
    double q;
    if (b < 0)
        q = (-b - distSqrt)/2.0;
    else
        q = (-b + distSqrt)/2.0;

    /* Compute t0 and t1. */
    double t0 = q / a;
    double t1 = c / q;

    /* Make sure t0 is smaller than t1. */
    if (t0 > t1)
    {
        /* If t0 is bigger than t1, swap them around. */
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    /* If t1 is less than zero, the object is in the ray's negative direction
     * and consequently, the ray misses the sphere.
     * Also, if the intersection point is the same as the starting point, we
     * simply ignore it.
     */
    if (t0 <= EPSLON && t1 <= EPSLON)
        return false;

    /* Now, we need to save both furthest and closest points, because we need the
     * closest to perform a regular intersection, and the furthest to perform, if
     * necessary, refractions.
     */

    /* If t0 is less than zero, the intersection point is at t1. */
    if (t0 <= EPSLON)
    {
	rT0 = t1;
        rT1 = EPSLON;
    }
    /* Else, the intersection point is at t0. */
    else
    {
	rT0 = t0;
        rT1 = t1;
    }

    /* We have to check if intersection point is beyond the light
     * or not.
     */
    if (ray.isToLightRay())
        if (rT0 > ray.getToLightDistance())
            return false;

    return true;
}

/* Sets the new direction of the ray after an intersection.
 * See more at:
 * http://en.wikipedia.org/wiki/Ray_tracing_(graphics)
 */
void Sphere::newDirection(Ray& ray, double& t)
{
    vector normal;

    /* First, we calculate the normal.
     * n = (y - c) / ||y - c||
     * Where y is the intersection point and c the centre
     * of the sphere.
     */
    normal = ray.getOrigin() + t*ray.getDir() - centre;

    /* Now, we update the start of the ray, which
     * is the intersection point.
     */
    ray.setOrigin(ray.getOrigin() + t*ray.getDir());

    /* Then, calculates the normal. */
    double length = sqrtf(normal*normal);
    normal /= length;

    /* With the normal calculated, we find the new direction
     * vector.
     * r = d - 2(n.d)n
     * Where d is the old direction and n is the normal.
     * TODO: That outter n is inner or external product?
     */
    ray.setDirection(ray.getDir() - 2*(ray.getDir()*normal)*normal);

    ray.normalize();

    return;

}

void Sphere::refractionRedirection(Ray &ray, double t)
{
    /* First, we calculate the outgoing point of this
     * ray in the sphere.
     */
    //printf("Before: %lf %lf %lf\n", ray.getOrigin().x,ray.getOrigin().y, ray.getOrigin().z);
    ray.setOrigin(ray.getOrigin() + t*ray.getDir());
    //printf("After: %lf %lf %lf\n", ray.getOrigin().x,ray.getOrigin().y, ray.getOrigin().z);

    //printf("With %lf\n", t);

    return;
}

void Sphere::intersectionPointNormal(Ray &ray, vector &normalInt)
{
    normalInt = ray.getOrigin() - centre;
    normalInt /= sqrtf(normalInt*normalInt);

    return;
}

/* Returns the radius of the sphere. */
double Sphere::getRadius() { return radius; }