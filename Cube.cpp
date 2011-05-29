#include <stdio.h>
/* Defines the needed classes and their headers. */
#include "Cube.h"
#include "Object.h"
#include "Ray.h"

Cube::Cube(double x, double y, double z, double xSide, double ySide, double zSide, double rC, double gC, double bC)
{
    centre.x = x;
    centre.y = y;
    centre.z = z;
    c.r = rC;
    c.g = gC;
    c.b = bC;

    /* Now, defines each vertix. */
    /* - - - */
    vertixes[0].x = x - xSide/2;
    vertixes[0].y = y + ySide/2;
    vertixes[0].z = z - zSide/2;
    /* - - - */
    vertixes[1].x = x + xSide/2;
    vertixes[1].y = y + ySide/2;
    vertixes[1].z = z - zSide/2;
    /* - - - */
    vertixes[2].x = x + xSide/2;
    vertixes[2].y = y - ySide/2;
    vertixes[2].z = z - zSide/2;
    /* - - - */
    vertixes[3].x = x - xSide/2;
    vertixes[3].y = y - ySide/2;
    vertixes[3].z = z - zSide/2;
    /* - - - */
    vertixes[4].x = x - xSide/2;
    vertixes[4].y = y + ySide/2;
    vertixes[4].z = z + zSide/2;
    /* - - - */
    vertixes[5].x = x + xSide/2;
    vertixes[5].y = y + ySide/2;
    vertixes[5].z = z + zSide/2;
    /* - - - */
    vertixes[6].x = x + xSide/2;
    vertixes[6].y = y - ySide/2;
    vertixes[6].z = z + zSide/2;
    /* - - - */
    vertixes[7].x = x - xSide/2;
    vertixes[7].y = y - ySide/2;
    vertixes[7].z = z + zSide/2;

    /* And the normals for each face. */
    vector normal;

    /* Front face. */
    normal.x = 0;
    normal.y = 0;
    normal.z = -1;
    normals[0] = normal;
    /* Right face. */
    normal.x = 1;
    normal.y = 0;
    normal.z = 0;
    normals[1] = normal;
    /* Bottom face. */
    normal.x = 0;
    normal.y = -1;
    normal.z = 0;
    normals[2] = normal;
    /* Left face. */
    normal.x = -1;
    normal.y = 0;
    normal.z = 0;
    normals[3] = normal;
    /* Back face. */
    normal.x = 0;
    normal.y = 0;
    normal.z = 1;
    normals[4] = normal;
    /* Top face. */
    normal.x = 0;
    normal.y = 1;
    normal.z = 0;
    normals[5] = normal;
}

Cube::Cube() {}
//Destructor
Cube::~Cube() {}


bool Cube::intersects(Ray &ray, double &rT0, double &rT1)
{
    int i;
    point v;
    vector n;

    /* In a cube, we will have at most two intersections.*/
    double intersections[2];
    vector intNormal[2];
    int interCounter = 0;

    /* Each face of the cube. We can only have two intersections at most in a cube. */
    for (i = 0; i < 6 && interCounter < 2; i++)
    {
        /* Due to the previous configuration, we can automatically choose
         * a normal a vertix belonging to the face number i.
         */
        n = normals[i];
        v = vertixes[i];

        double numerator = (v - ray.getOrigin())*n;
        double denominator = ray.getDir()*n;

        /* The ray is parallel to the plane. Can be either
         * inside the plane or outside it.
         */
        if (denominator == 0)
            continue;

        rT0 = numerator/denominator;
        /* Just to make sure we invalidate rT1. */
        rT1 = EPSLON;

        /* We are only looking for forward intersections. */
        if (rT0 <= EPSLON)
            continue;

        bool locallyIntersects = false;
        /* We have to calculate the intersection point, to know if it hits
         * a face or only the plane that contains the face.
         */
        point iP = ray.getOrigin() + rT0*ray.getDir();
        
        switch(i)
        {

            /* Front face. */
            case (0):
                if (iP.x >= vertixes[0].x && iP.x <= vertixes[1].x &&
                    iP.y >= vertixes[3].y && iP.y <= vertixes[1].y)
                {
                    intNormal[interCounter] = n;
                    intersections[interCounter++] = rT0;
                    locallyIntersects = true;
                }
                break;
            /* Right face. */
            case (1):
                if (iP.z >= vertixes[1].z && iP.z <= vertixes[5].z &&
                    iP.y >= vertixes[2].y && iP.y <= vertixes[1].y)
                {
                    intNormal[interCounter] = n;
                    intersections[interCounter++] = rT0;
                    locallyIntersects = true;
                }
                break;
            /* Bottom face. */
            case (2):
                break;
                if (iP.x >= vertixes[3].x && iP.x <= vertixes[2].x &&
                    iP.z >= vertixes[3].z && iP.z <= vertixes[7].z)
                {
                    intNormal[interCounter] = n;
                    intersections[interCounter++] = rT0;
                    locallyIntersects = true;
                }
                break;
            /* Left face. */
            case (3):
                break;
                if (iP.z >= vertixes[0].z && iP.z <= vertixes[4].z &&
                    iP.y >= vertixes[3].y && iP.y <= vertixes[0].y)
                {
                    intNormal[interCounter] = n;
                    intersections[interCounter++] = rT0;
                    locallyIntersects = true;
                }
                break;
            /* Back face. */
            case (4):
                break;
                if (iP.x >= vertixes[4].x && iP.x <= vertixes[5].x &&
                    iP.y >= vertixes[7].y && iP.y <= vertixes[4].y)
                {
                    intNormal[interCounter] = n;
                    intersections[interCounter++] = rT0;
                    locallyIntersects = true;
                }
                break;
            /* Top face. */
            case (5):
                break;
                if (iP.x >= vertixes[0].x && iP.x <= vertixes[1].x &&
                    iP.z >= vertixes[0].z && iP.z <= vertixes[4].z)
                {
                    intNormal[interCounter] = n;
                    intersections[interCounter++] = rT0;
                    locallyIntersects = true;
                }
                break;

            /* We have to check if intersection point is beyond the light
             * or not.
             */
            if (ray.isToLightRay() && locallyIntersects)
            {
                /* If this is a toLightRay, we are only looking for a intersection,
                 * so we can stop right now. If this distance is greater, we don't
                 * increment the counter and the method will return false.
                 */
                if (rT0 > ray.getToLightDistance())
                    continue;
            }
        }
    }

    
    if (interCounter > 0)
    {
        if (interCounter == 1)
        {
            rT0 = intersections[0];
            intersectionNormal = intNormal[0];
        }
        else
        {
            if (intersections[0] < intersections[1])
            {
                rT0 = intersections[0];
                rT1 = intersections[1];
                intersectionNormal = intNormal[0];
            }
            else
            {
                rT1 = intersections[0];
                rT0 = intersections[1];
                intersectionNormal = intNormal[1];
            }
        }
        return true;
    }
    else
        return false;
}

void Cube::newDirection(Ray &ray, double &t)
{
    /* Sets the new origin of the ray. */
    ray.setOrigin(ray.getOrigin() + t*ray.getDir());

    /* And then, its new direction. */
    ray.setDirection(ray.getDir() - 2*(ray.getDir()*intersectionNormal)*intersectionNormal);

    ray.normalize();

    return;

}

/* In a plane, with no thickness, the ray will continue to move. Therefore, the
 * starting point of the ray will be the same as the intersection point and the
 * direction of the ray won't change.
 */
bool Cube::refractionRedirection(Ray &ray, double t0, double t1)
{
    if (t0 <= EPSLON)
        return false;
    
    ray.setOrigin(ray.getOrigin() + t0*ray.getDir());
    
    return true;
}

void Cube::intersectionPointNormal(Ray &ray, vector &normalInt)
{
    /* At a cube, the normal at the intersection point is the
     * normal of the intersected face.
     */
    normalInt = intersectionNormal;

    return;
}

/* Returns the normals of each face. */
vector Cube::getNormalFront() {return normals[0];}
vector Cube::getNormalBack() {return normals[4];}
vector Cube::getNormalBottom() {return normals[2];}
vector Cube::getNormalTop()  {return normals[5];}
vector Cube::getNormalRight() {return normals[1];}
vector Cube::getNormalLeft() {return normals[3];}
void Cube::setNormalFront(vector v) {normals[0] = v;}
void Cube::setNormalBack(vector v) {normals[4] = v;}
void Cube::setNormalBottom(vector v) {normals[2] = v;}
void Cube::setNormalTop(vector v) {normals[5] = v;}
void Cube::setNormalRight(vector v) {normals[1] = v;}
void Cube::setNormalLeft(vector v) {normals[3] = v;}