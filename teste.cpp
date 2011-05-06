#include <stdio.h>
#include <math.h>
#include "BasicStructures.h"
#include "Ray.h"
#include "Sphere.h"

#define R_X 220
#define R_Y 170
#define R_Z -1000

#define S_X 225
#define S_Y 120
#define S_Z 100
#define S_R 160

#define L_X 1
#define L_Y 1
#define L_Z 1
 
struct ray 
{
	point start;
	vector dir;

};

struct sphere 
{
	point centre;
	double r;

};

 bool hitSphere(ray r, sphere s, double &t) 
 { 
    // Intersection of a ray and a sphere
    // Check the articles for the rationale
    // NB : this is probably a naive solution
    // that could cause precision problems
    // but that will do it for now. 
    vector dist = s.centre - r.start; 
    double B = r.dir * dist;
    double D = B*B - dist * dist + s.r * s.r; 
    if (D < 0.0f) 
        return false; 
    double t0 = B - sqrtf(D); 
    double t1 = B + sqrtf(D);
    bool retvalue = false;  
    if ((t0 > 0.1f) && (t0 < t)) 
    {
        t = t0;
        retvalue = true; 
    } 
    if ((t1 > 0.1f) && (t1 < t)) 
    {
        t = t1; 
        retvalue = true; 
    }
    return retvalue; 
 }

 int draw() 
 {
	ray viewRay = { {R_X, R_Y, R_Z}, { 0.0f, 0.0f, 1.0f}};
	sphere sphere = { {S_X, S_Y, S_Z}, S_R};

	// Looking for the closest intersection
	double t = 2000.0f;

	if (!hitSphere(viewRay, sphere, t)) 
		{
			printf("Doesn't intersect.\n");
			return 0;
		}
		
	printf("Intersects at %lf.\n", t);
	point newStart = viewRay.start + t * viewRay.dir; 

	// What is the normal vector at the point of intersection ?
	// It's pretty simple because we're dealing with spheres
	vector n = newStart - sphere.centre;
	double temp = n * n;
	if (temp == 0.0f) 
	{
		printf("Here\n");
		return 0;
	}

	temp = 1.0f / sqrtf(temp); 
	n = temp * n; 

	double reflet = 2.0f * (viewRay.dir * n);
	viewRay.start = newStart;
	viewRay.dir = viewRay.dir - reflet * n;  
	
	printf("The new starting point is %lf %lf %lf.\n The new direction is %lf %lf %lf.\n",
			viewRay.start.x, viewRay.start.y, viewRay.start.z,
			  viewRay.dir.x, viewRay.dir.y, viewRay.dir.z);
	
	return 0;
 }
 
 
 bool intersects(ray r, sphere s, double &t)
{
    /* Compute a, b and c coefficients. */
	//a = (x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2
    double a = r.dir*r.dir;
	//b = 2[ (x2 - x1) (x1 - x3) + (y2 - y1) (y1 - y3) + (z2 - z1) (z1 - z3) ]
	double b = 2*(r.dir*(r.start - s.centre));
	//c = x3^2 + y3^2 + z3^2 + x1^2 + y1^2 + z1^2 - 2[x3.x1 + y3.y1 + z3.z1] - r^2
    double c = s.centre*s.centre + r.start*r.start - 2*(r.start*s.centre) - s.r*s.r;

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
    if (t1 <= 0 || t0 <= 0)
        return false;

    /* If t0 is less than zero, the intersection point is at t1. */
    if (t0 < 0)
		t = t1;
    /* Else, the intersection point is at t0. */
    else
		t = t0;
	
	return true;
}
 
 void rayTracer()
{
	int i, z, index;
	double t;
	Ray ray = Ray(R_X,R_Y,R_Z, 0, 0);
	ray.setDirection(0,0,1.0);
	ray.normalize();
	Sphere sphere = Sphere(S_X,S_Y,S_Z, S_R, 0.15, 1, 0, 0);
	
	//if (depth > 3)
	//	printf("DEPTH IS %d\n", depth);
	
	/* Goes throught all the objects. TODO: Improve this to more objects. */
	if (!sphere.intersects(ray, t))
		{
			printf("Doesn't intersect\n");
			return;
		}
	printf("Intersects at %lf.\n", t);
	/* Calculate the new direction of the ray. */
	ray.newDirection(t, sphere);
	
	printf("The new starting point is %lf %lf %lf.\n The new direction is %lf %lf %lf.\n",
			ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z,
			  ray.getDir().x, ray.getDir().y, ray.getDir().z);
	

	return;
}
 
 int main()
 {
	draw();
	rayTracer();
 }