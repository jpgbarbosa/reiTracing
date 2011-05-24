#include <stdio.h>
/* Defines the needed classes and their headers. */
#include "Sphere.h"
#include "Ray.h"
#include "Light.h"
#include "Plane.h"
#include "BasicStructures.h"
#include "Object.h"

extern int noObjects, noLights;
extern Object **objects;
extern Light *lights;

/* SCENE DESCRIPTION:
 *    -> There is one ground plane and another at the right, working as a mirror.
 *       In between, there are two spheres, one made of glass and another as
 *       a mirror.
 */
void sceneOne()
{
    /* First, allocates enough space for all the structures.*/
    noObjects = 4;
    noLights = 2;

    objects = new Object *[noObjects];
    lights = new Light[noLights];

    /* Spheres initialization. */
    Sphere *sphere = new Sphere(500.0,300, 4300.0, 80.0, 0.0, 0.0, 0.0);
    (*sphere).setReflection(0.9);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(0.0, 0.0, 0.0);
    (*sphere).setRefraction(0.0);

    objects[0] = sphere;
    
    sphere = new Sphere(400.0,300.0, 100.0, 50.0, 0.0, 0.0, 0.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(80);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(0.0, 0.0, 0.0);
    (*sphere).setRefraction(0.8);

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

    /* Lights initialization. */
    lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[1] = Light(300,400,-6000, 1.0, 1, 1, 1);
}

/* SCENE DESCRIPTION:
 *    -> There is one ground plane and two spheres, one blue and another red.
 */
void sceneTwo()
{
    /* First, allocates enough space for all the structures.*/
    noObjects = 3;
    noLights = 1;

    objects = new Object *[noObjects];
    lights = new Light[noLights];

    /* Spheres initialization. */
    Sphere *sphere = new Sphere(500.0,300, 300.0, 80.0, 1.0, 0.0, 0.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(1.0, 0.0, 0.0);
    (*sphere).setRefraction(0.0);

    objects[0] = sphere;

    sphere = new Sphere(380.0,220.0, 100.0, 50.0, 0.0, 0.0, 1.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(0.0, 0.0, 1.0);
    (*sphere).setRefraction(0.0);

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

    /* Lights initialization. */
    lights[0] = Light(300,10000,-6000, 1.0, 1, 1, 1);
}

/* SCENE DESCRIPTION:
 *    -> There is one ground plane and two spheres, one blue and another red.
 */
void sceneThree()
{
    /* First, allocates enough space for all the structures.*/
    noObjects = 5;
    noLights = 2;

    objects = new Object *[noObjects];
    lights = new Light[noLights];

    /* Spheres initialization. */
    Sphere *sphere = new Sphere(500.0,300, 4300.0, 80.0, 0.0, 0.0, 0.0);
    (*sphere).setReflection(0.9);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(0.0, 0.0, 0.0);
    (*sphere).setRefraction(0.0);

    objects[0] = sphere;

    sphere = new Sphere(380.0,220.0, 4100.0, 50.0, 0.0, 0.0, 1.0);
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
    plane = new Plane(0,0,20000, normalTwo, 0.6,0.8,0.2);
    (*plane).setReflection(0.2);
    (*plane).setShininess(50);
    (*plane).setSpecular(0.2, 0.2, 0.2);
    (*plane).setDiffuse(0.6, 0.8, 0.2);
    (*plane).setRefraction(0);

    objects[4] = plane;

    /* Lights initialization. */
    lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[1] = Light(300,400,-6000, 1.0, 1, 1, 1);
}

/* SCENE DESCRIPTION:
 *    -> Sea theme.
 */
void sceneFour()
{
    /* First, allocates enough space for all the structures.*/
    noObjects = 4;
    noLights = 2;

    objects = new Object *[noObjects];
    lights = new Light[noLights];

    /* Spheres initialization. */
    Sphere *sphere = new Sphere(480.0,300, 100.0, 80.0, 0.0, 0.0, 0.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(0.0, 0.0, 0.0);
    (*sphere).setRefraction(0.3);

    objects[0] = sphere;

    sphere = new Sphere(380.0,280.0, 300.0, 50.0, 0.0, 0.0, 1.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setDiffuse(0.0, 0.0, 0.9);
    (*sphere).setRefraction(0.0);

    objects[1] = sphere;

    /* Planes initialization. */

    /* Ground. */
    vector normalZero = {0, 1, 0};
    Plane *plane = new Plane(0,0,0, normalZero, 0.0,0.0,0.3);
    (*plane).setReflection(0.5);
    (*plane).setShininess(20);
    (*plane).setSpecular(0.6, 0.6, 0.6);
    (*plane).setDiffuse(0.0, 0.0, 0.3);
    (*plane).setRefraction(0.0);

    objects[2] = plane;

    /* Back wall.*/
    vector normalTwo = {0, 0, -1};
    plane = new Plane(0,0,100000, normalTwo, 0.1,0.1,0.8);
    (*plane).setReflection(0.5);
    (*plane).setShininess(0.1);
    (*plane).setSpecular(0.1, 0.1, 0.1);
    (*plane).setDiffuse(0.1, 0.1, 0.8);
    (*plane).setRefraction(0);

    objects[3] = plane;

    /* Lights initialization. */
    lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[1] = Light(300,10000,-6000, 1.0, 1, 1, 1);
}

/* No works at the scene selection. */
void buildScene(int no)
{
    /* Selects the right scenario to be built. */
    switch(no)
    {
        case 1: sceneOne(); return;
        case 2: sceneTwo(); return;
        case 3: sceneThree(); return;
        case 4: sceneFour(); return;
        default: sceneOne(); printf("WARNING: No valid scenarion has been choosen. Will set scenario one...\n");
    }

    return;
}