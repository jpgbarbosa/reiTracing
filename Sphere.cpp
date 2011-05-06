#include "Sphere.h"

/* In the constructor, we set the starting point of the ray. */
Sphere::Sphere(double x, double y, double z, double rad, double rC, double gC, double bC):
	radius(rad)
{
    /* Creates the parent class. */
    Object(x, y, z, rC, gC, bC);
}

Sphere::Sphere() { Object(); }
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
bool Sphere::intersects(Ray &ray, double &t)
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
    if (t1 <= EPSLON || t0 <= EPSLON)
        return false;

    /* If t0 is less than zero, the intersection point is at t1. */
    if (t0 < 0)
		t = t1;
    /* Else, the intersection point is at t0. */
    else
		t = t0;
	
	return true;
}

/* Returns centre and radius of the sphere. */
point Sphere::getCentre() { return centre; }
double Sphere::getRadius() { return radius; }