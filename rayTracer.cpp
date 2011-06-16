/* Defines the needed classes and their headers. */
#include "Sphere.h"
#include "Ray.h"
#include "Light.h"
#include "Plane.h"
#include "BasicStructures.h"
#include "Object.h"
#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

/* External variables. */
extern int noObjects, noLights;
extern Object **objects;
extern Light *lights;
extern point camera;
extern int screenWidth, screenHeight, screenSize;
extern colour image[SCREEN_W][SCREEN_H];
extern int visualizationType;

/* All the coefficients that will make the plane.
 * a,b and c will go for x, y, z, while d is for the constant.
 * A plane can be defined as a.x + b.y + c.z = d;
 *
/* initX and initY will define the beginning of the view plane.
 * For example, if we have an initX and initY equal to zero, it means
 * that the plane will be a rectangle with the lower left corner standing
 * on the coordinate x = 0 and y = 0;
 */
double setViewPlaneZCoordinate(double a, double b, double c, double d, double initX, double initY, int x, int y)
{
    
    return (d - a*(initX + x) - b*(initY + y));

}

void rayTracer(Ray ray, int depth)
{
    int i, z, index;
    double minT0 = -1, minT1 = -1, t0, t1;

    /* Goes through all the objects in the scene. */
    for (i = 0; i < noObjects; i++)
        if (objects[i]->intersects(ray, t0, t1))
        {
            /* Finds the closest. */
            if (t0 < minT0 || minT0 == -1)
            {
                minT0 = t0;
                minT1 = t1;
                index = i;
            }
        }

    /* We have found at least one intersection. */
    if (minT0 != -1)
    {
        /* Used in the Blinn-Phong calculation. */
        vector oldDir = ray.getDir();

        /* There can be also refraction. In that case, we start a new call
         * of the function and from this moment on, the ray splits into two.
         */
        if (objects[index]->getRefraction() > 0)
        {
           Ray refractionRay = ray;

           /* Sets the new starting point of the ray, at the 'other
            * side' of the object. This point was previously calculated
            * at the intersection function. Also, if there is some problem
            * with this point (i.e., not a valid point, due, maybe, to the
            * the fact that the ray only intersects the object at one point),
            * the method return false and we won't make the recursive call.
            */
           if (objects[index]->refractionRedirection(refractionRay, minT0, minT1))
           {
               /* Sets the new intensity of the ray. */
               refractionRay.setIntensity(refractionRay.getIntensity()*objects[index]->getRefraction());

               /* Recursively starts a new ray, now for the refraction. */
               rayTracer(refractionRay, depth + 1);
           }
        }

        /* Calculate the new direction of the ray. */
        objects[index]->newDirection(ray, minT0);

        /* Then, calculate the lighting at this point. */
        for (z = 0; z < noLights; z++)
        {
            /* The directional vector between the intersection point and the light. */
            vector toLight, normal;
            toLight = lights[z].getCentre() - ray.getOrigin();

            /* We also need to calculate the normal at the intersection point. */
            objects[index]->intersectionPointNormal(ray, normal);

            /* The transparent coefficient is used when we are looking for intersections
             * between the intersection point and the lights (to know if we are in the
             * shadow of another object or not). However, transparent objects (with refraction
             * greater than 0.0), will count as intersections, but we know that they will still
             * allow some light to pass. Therefore, we have to keep a coefficient that will
             * go to 0.0 in case we find an opaque object between the intersection point
             * and the light.
             */
            double transparencyCoef = 1.0;

            /* If the normal is perpendicular or is in opposite direction of the light,
             * we can skip this light because it's not going to light the intersection
             * point.
             */
            if (normal * toLight < EPSLON)
                continue;

            /* Now, we have to see if we are in the shadow of any other object.
             * For that, we create a temporary ray that goes from the intersection
             * point to the light spot.
             */
            Ray toLightRay = Ray(ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z, 0, 0);
            toLightRay.setDirection(toLight);
            toLightRay.setIsToLight(true, sqrtf(toLightRay.getDir() * toLightRay.getDir()));
            toLightRay.normalize();

            for (i = 0; i < noObjects && transparencyCoef > EPSLON; i++)
                /* It can't intersect with itself. */
                if (objects[i]->intersects(toLightRay, t0, t1) && index != i)
                    transparencyCoef *= objects[i]->getRefraction();

            /* We aren't in shadow of any other object. Therefore, we have to calculate
             * the contribution of this light to the final result.
             */
            if (transparencyCoef > EPSLON)
            {
                /* The Lambert Effect. Depending on the direction of the light, it might
                 * be more or less intense.
                 */
                double lambert = (toLightRay.getDir() * normal * ray.getIntensity());

                /* Updates the colour of the ray. */
                /* The smaller the transparency coefficient is, the darker is the shadow produced
                 * by the objects.
                 */
                ray.increaseR(lambert*lights[z].getR()*objects[index]->getR() * transparencyCoef * lights[z].getFade(toLightRay.getToLightDistance()));
                ray.increaseG(lambert*lights[z].getG()*objects[index]->getG() * transparencyCoef * lights[z].getFade(toLightRay.getToLightDistance()));
                ray.increaseB(lambert*lights[z].getB()*objects[index]->getB() * transparencyCoef * lights[z].getFade(toLightRay.getToLightDistance()));

                /* The Blinn-Phong Effect.
                 * The direction of Blinn is exactly at mid point of the light ray
                 * and the view ray.
                 * We compute the Blinn vector and then we normalize it
                 * then we compute the coeficient of blinn
                 * which is the specular contribution of the current light.
                 */
                vector blinnDir = toLightRay.getDir() - oldDir;
                double internProd = blinnDir * blinnDir;

                if (internProd != 0.0 )
                {
                    double fViewProjection = oldDir * normal;
                    double fLightProjection = toLightRay.getDir() * normal;

                    /* Calculates the coeficient and then applies it to each colour component. */
                    double blinnCoef = 1.0/sqrtf(internProd) * max(fLightProjection - fViewProjection , 0.0);
                    blinnCoef = ray.getIntensity() * powf(blinnCoef, objects[index]->getShininess());
                    /* The smaller the transparency coefficient is, the darker is the shadow produced
                     * by the objects.
                     */
                    ray.increaseR(blinnCoef * objects[index]->getSpecular().r  * lights[z].getIntensity() * transparencyCoef * lights[z].getFade(toLightRay.getToLightDistance()));
                    ray.increaseG(blinnCoef * objects[index]->getSpecular().g  * lights[z].getIntensity() * transparencyCoef * lights[z].getFade(toLightRay.getToLightDistance()));
                    ray.increaseB(blinnCoef * objects[index]->getSpecular().b  * lights[z].getIntensity() * transparencyCoef * lights[z].getFade(toLightRay.getToLightDistance()));
                }
            } /* if (!inShadow)*/
        }

        ray.multIntensity(objects[index]->getReflection());
    }

    /* We have reached the limit of recursivity for ray tracing.
     * Consequently, we assume that we can't reach the light and
     * therefore, the pixel colour will be black, corresponding
     * to the absence of colour.
     * If we don't have any intersection, there's no point keep
     * calculating the ray tracing. Also, the ray might not carry
     * any more energy.
     */
    if (minT0 == -1 || depth == MAX_DEPTH || ray.getIntensity() <= EPSLON)
    {
        ray.normalizeColour();
        image[ray.getHPos()][ray.getWPos()].r += ray.getR();
        image[ray.getHPos()][ray.getWPos()].g += ray.getG();
        image[ray.getHPos()][ray.getWPos()].b += ray.getB();
    }
    /* We need to move to the next level of recursivity. */
    else
            rayTracer(ray, depth + 1);

    return;
}

/* Type will define whether we are rendering the lower part of the image
 * or the upper.
 */
void *renderImage(void *type)
{
    int x, y;
    double z = 0;
    int limitY;
    
    /* Top rendering. */
    if ((*(int* )type) == 0)
    {
        printf("One thread here.\n");
        y = 0;
        limitY = screenHeight/2;
    
    } else  /* Lower rendering. */
    {
        printf("Another thread here.\n");
        y = screenHeight/2;
        limitY = screenHeight;

    }

    /* Counter used to be printing information on the screen about the
     * state of the rendering.
     */
    int perCounter = 0;

    for (; y < limitY; y++)
    {
            for (x = 0; x < screenWidth; x++)
            {
                /* Orthogonal Perspective
                Ray ray(x,y,-1000.0, y, x);
                ray.setDirection(0,0,1.0);
                 */

                /* Parameters:
                 *  a , b, c, d, initX, initY, x, y
                 */
                if (visualizationType == LOOKING_AHEAD)
                {
                    z = setViewPlaneZCoordinate(0, 0, 1, 0, 0, 0, x,y);

                    /* Conic Perspective. */
                    Ray ray(x,y, z, y, x);
                    point pixelPoint = {0.5 + x, 0.5 + y, z};
                    vector dir = pixelPoint - camera;
                    ray.setDirection(dir);
                    ray.normalize();
                    //printf("%lf %lf %lf\n", ray.getDir().x, ray.getDir().y, ray.getDir().z);
                    rayTracer(ray, 0);
                }
                else if (visualizationType == LOOKING_DOWN)
                {
                    //z = setViewPlaneZCoordinate(0, 1, 0, 0, 500, 100, x,y);
                    z = 1000;
                    /* Conic Perspective. */
                    Ray ray(x,z, y, y, x);
                    point pixelPoint = {0.5 + x, z, 0.5 + y};
                    vector dir = pixelPoint - camera;
                    ray.setDirection(dir);
                    ray.normalize();
                    //printf("%lf %lf %lf\n", ray.getDir().x, ray.getDir().y, ray.getDir().z);
                    rayTracer(ray, 0);
                }
        }

        /* If it's an even number, we will display the image, because we already
         * have some information to do so.
         */
        if ((y & 1) == 0)
            glutPostRedisplay();
    }
}