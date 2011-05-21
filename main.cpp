#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

/* Defines the needed classes and their headers. */
#include "Sphere.h"
#include "Ray.h"
#include "Light.h"
#include "Plane.h"
#include "BasicStructures.h"
#include "Object.h"

#define SCREEN_W 800
#define SCREEN_H 600
#define MAX_DEPTH 10
#define NO_SPHERES 2
#define NO_LIGHTS 2
#define NO_PLANES 3
#define NO_OBJECTS 5

#define ANTIALIASING_LIMIT 0.4

using namespace std;
/* The screen definition. */
int screenWidth = SCREEN_W;
int screenHeight = SCREEN_H;
int screenSize = SCREEN_W*SCREEN_H;

/* This array will hold all the colours for all the pixels in the screen. */
colour image[SCREEN_W][SCREEN_H];

/* Definition of all objects in the scene, as well as the camera. */
point camera;

int noObjects = NO_OBJECTS;
Object *objects[NO_OBJECTS];

int noLights = NO_LIGHTS;
Light lights[NO_LIGHTS];

double min(double t, double v)
{
    if (t < v)
        return t;

    return v;
}

void rayTracer(Ray ray, int depth)
{
    int i, z, index;
    double minT0 = -1, minT1 = -1, t0, t1;
    /* So we can know the object that this ray intersects. */
    int intersectionType = -1;

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
                intersectionType = objects[i]->getIntersectionType();
            }
        }
	
    /* We have found at least one intersection. */
    if (minT0 != -1)
    {
        //if (index == 0)
        //    printf("Got here at index %i and %lf %lf!\n", index, minT0, minT1);
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
            if (normal * toLight < -EPSLON)
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
                ray.increaseR(lambert*lights[z].getR()*objects[index]->getR() * transparencyCoef);
                ray.increaseG(lambert*lights[z].getG()*objects[index]->getG() * transparencyCoef);
                ray.increaseB(lambert*lights[z].getB()*objects[index]->getB() * transparencyCoef);

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
                    ray.increaseR(blinnCoef * objects[index]->getSpecular().r  * lights[z].getIntensity() * transparencyCoef);
                    ray.increaseG(blinnCoef * objects[index]->getSpecular().g  * lights[z].getIntensity() * transparencyCoef);
                    ray.increaseB(blinnCoef * objects[index]->getSpecular().b  * lights[z].getIntensity() * transparencyCoef);
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

void renderImage()
{
    int x, y;

    for (y = 0; y < screenHeight; y++)
            for (x = 0; x < screenWidth; x++)
            {
                /* Orthogonal Perspective
                Ray ray(x,y,-1000.0, y, x);
                ray.setDirection(0,0,1.0);
                 */
                /* Conic Perspective. */
                Ray ray(x,y, 0.0, y, x);
                point pixelPoint = {0.5 + x, 0.5 + y, 0.0};
                vector dir = pixelPoint - camera;
                ray.setDirection(dir);
                ray.normalize();
                rayTracer(ray, 0);

                /* TODO: Antialiasing, doesn't seem to be working. */
                /*Ray ray(x,y, 0.0, y, x);
                vector dir;
                point pixelPoint;
                colour finalColour;
                finalColour.r = 0.0;
                finalColour.g = 0.0;
                finalColour.b = 0.0;

                pixelPoint.x = 0.5 + x;
                pixelPoint.y = 0.5 + y;
                pixelPoint.z = 0.0;
                dir = pixelPoint - camera;
                ray.setDirection(dir);
                ray.normalize();
                rayTracer(ray, 0);
                finalColour = finalColour + image[ray.getHPos()][ray.getWPos()];
                image[ray.getHPos()][ray.getWPos()] = 0.0;

                pixelPoint.x = 0.5 + x;
                pixelPoint.y = y;
                pixelPoint.z = 0.0;
                dir = pixelPoint - camera;
                ray.setDirection(dir);
                ray.normalize();
                rayTracer(ray, 0);
                finalColour = finalColour + image[ray.getHPos()][ray.getWPos()];
                image[ray.getHPos()][ray.getWPos()] = 0;

                pixelPoint.x = x;
                pixelPoint.y = 0.5 + y;
                pixelPoint.z = 0.0;
                dir = pixelPoint - camera;
                ray.setDirection(dir);
                ray.normalize();
                rayTracer(ray, 0);
                finalColour = finalColour + image[ray.getHPos()][ray.getWPos()];
                image[ray.getHPos()][ray.getWPos()] = 0.0;

                pixelPoint.x = x;
                pixelPoint.y = y;
                pixelPoint.z = 0.0;
                dir = pixelPoint - camera;
                ray.setDirection(dir);
                ray.normalize();
                rayTracer(ray, 0);
                finalColour = finalColour + image[ray.getHPos()][ray.getWPos()];
                image[ray.getHPos()][ray.getWPos()] = finalColour / 4;*/
        }
}


void display()
{
    int i, j, k,  aliasingTimes = 1;

    /* Passes into an array all the colours gathered in the matrix
     * image, so we can use it in the DrawPixels.
     */
    float* pixels = new float[screenSize*3];

    for( i = 0; i < screenHeight; i++)
            for (j = 0; j < screenWidth; j++)
            {
                    pixels[i*(screenWidth*3) + j*3] = image[j][i].r;
                    pixels[i*(screenWidth*3) + j*3 + 1] = image[j][i].g;
                    pixels[i*(screenWidth*3) + j*3 + 2] = image[j][i].b;
            }
    /* Antialiasing techniques:
     * Given all the calculated colours from the ray tracing process, we
     * pick up all the values around it and calculate its mean. That mean
     * will be the final colour of the pixel.
     */
    for (k = 0; k < aliasingTimes; k++)
    {
        for( i = 1; i < screenHeight - 1; i++)
        {
            for (j = 1; j < screenWidth - 1; j++)
            {
                /* RED. */
                double value;
                value = pixels[(i-1)*(screenWidth*3) + (j-1)*3]
                            + pixels[(i-1)*(screenWidth*3) + j*3]
                              + pixels[(i-1)*(screenWidth*3) + (j+1)*3]
                                + pixels[i*(screenWidth*3) + (j-1)*3]
                                  + pixels[i*(screenWidth*3) + j*3]
                                    + pixels[i*(screenWidth*3) + (j+1)*3]
                                      + pixels[(i+1)*(screenWidth*3) + (j-1)*3]
                                        + pixels[(i+1)*(screenWidth*3) + j*3]
                                          + pixels[(i+1)*(screenWidth*3) + (j+1)*3];

                if (abs(pixels[i*(screenWidth*3) + j*3] - value / 9) > ANTIALIASING_LIMIT)
                    pixels[i*(screenWidth*3) + j*3] = value / 9;

                /* GREEN. */
                value = pixels[(i-1)*(screenWidth*3) + (j-1)*3 + 1]
                            + pixels[(i-1)*(screenWidth*3) + j*3 + 1]
                              + pixels[(i-1)*(screenWidth*3) + (j+1)*3 + 1]
                                + pixels[i*(screenWidth*3) + (j-1)*3 + 1]
                                  + pixels[i*(screenWidth*3) + j*3 + 1]
                                    + pixels[i*(screenWidth*3) + (j+1)*3 + 1]
                                      + pixels[(i+1)*(screenWidth*3) + (j-1)*3 + 1]
                                        + pixels[(i+1)*(screenWidth*3) + j*3 + 1]
                                          + pixels[(i+1)*(screenWidth*3) + (j+1)*3 + 1];

                if (abs(pixels[i*(screenWidth*3) + j*3 + 1] - value / 9) > ANTIALIASING_LIMIT)
                    pixels[i*(screenWidth*3) + j*3 + 1] = value / 9;

                /* BLUE. */
                value = pixels[(i-1)*(screenWidth*3) + (j-1)*3 + 2]
                            + pixels[(i-1)*(screenWidth*3) + j*3 + 2]
                              + pixels[(i-1)*(screenWidth*3) + (j+1)*3 + 2]
                                + pixels[i*(screenWidth*3) + (j-1)*3 + 2]
                                  + pixels[i*(screenWidth*3) + j*3 + 2]
                                    + pixels[i*(screenWidth*3) + (j+1)*3 + 2]
                                      + pixels[(i+1)*(screenWidth*3) + (j-1)*3 + 2]
                                        + pixels[(i+1)*(screenWidth*3) + j*3 + 2]
                                          + pixels[(i+1)*(screenWidth*3) + (j+1)*3 + 2];

                if (abs(pixels[i*(screenWidth*3) + j*3 + 2] - value / 9) > ANTIALIASING_LIMIT)
                    pixels[i*(screenWidth*3) + j*3 + 2] = value / 9;
            }
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Writes a block of pixels to the framebuffer. */
    glDrawPixels(screenWidth,screenHeight,GL_RGB,GL_FLOAT, pixels);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Our Fantastic Ray Tracer");

    /* Camera initialization. */
    camera.x = 300;
    camera.y = 400;
    camera.z = -5000;

    /* Spheres initialization. */
    Sphere *sphere = new Sphere(500.0,300, 300.0, 80.0, 0.0, 0.0, 0.0);
    (*sphere).setReflection(0.9);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(0.0, 0.0, 0.0);
    (*sphere).setRefraction(0.0);

    objects[0] = sphere;

    sphere = new Sphere(380.0,220.0, 100.0, 50.0, 0.0, 0.0, 1.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(0.0, 0.0, 0.9);
    (*sphere).setRefraction(0.0);

    /*sphere = new Sphere(450.0,300.0, 100.0, 50.0, 0.1, 0.1, 0.1);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(10);
    (*sphere).setSpecular(0.2, 0.2, 0.2);
    (*sphere).setDiffuse(0.2, 0.2, 0.2);
    (*sphere).setRefraction(0.5);*/

    objects[1] = sphere;

    /* Planes initialization. */

    /* Ground. */
    vector normalZero = {0, 1, 0};
    Plane *plane = new Plane(0,0,0, normalZero, 0.0,0.0,0.7);
    (*plane).setReflection(0.0);
    (*plane).setShininess(20);
    (*plane).setSpecular(0.6, 0.4, 0.2);
    (*plane).setDiffuse(0.0, 0.0, 0.7);
    (*plane).setRefraction(0);

    objects[2] = plane;

    /* Right wall. */
    vector normalOne = {-1, 0, 0};
    plane = new Plane(800,0,0, normalOne, 0.0,0.0,0.0);
    (*plane).setReflection(0.9);
    (*plane).setShininess(50);
    (*plane).setSpecular(1, 1, 1);
    (*plane).setDiffuse(0.0, 0.0, 0.0);
    (*plane).setRefraction(0);

    objects[3] = plane;

    /* Back wall.*/
    vector normalTwo = {0, 0, -1};
    plane = new Plane(0,0,15000, normalTwo, 0.0,0.0,0.0);
    (*plane).setReflection(0.9);
    (*plane).setShininess(10);
    (*plane).setSpecular(0.1, 0.1, 0.1);
    (*plane).setDiffuse(0.0, 0.0, 0.0);
    (*plane).setRefraction(0);

    objects[4] = plane;

    /* Lights initialization. */
    lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[1] = Light(300,400,-6000, 1.0, 1, 1, 1);

    // Starts the ray tracing process.
    renderImage();

    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    //glutMouseFunc(mouse_button);
    //glutMotionFunc(mouse_motion);
    //glutKeyboardFunc(keyboard);
    //glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glPointSize(2);

    glutMainLoop();
}