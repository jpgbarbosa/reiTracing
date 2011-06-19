#include <stdio.h>
#include <cmath>
/* Defines the needed classes and their headers. */
#include "Sphere.h"
#include "Cube.h"
#include "Ray.h"
#include "Light.h"
#include "Plane.h"
#include "PlaneChess.h"
#include "BasicStructures.h"
#include "Object.h"

extern int noObjects, noLights;
extern Object **objects;
extern Light *lights;
extern long long fadingCoeficient;
extern long long fullLightLimit;

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
    (*sphere).setRefraction(0.0);

    objects[0] = sphere;
    
    sphere = new Sphere(400.0,300.0, 100.0, 50.0, 0.0, 0.0, 0.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(80);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setRefraction(0.8);

    objects[1] = sphere;

    /* Planes initialization. */

    /* Ground. */
    vector normalZero = {0, 1, 0};
    Plane *plane = new Plane(0,0,0, normalZero, 0.0,0.0,0.7);
    (*plane).setReflection(0.0);
    (*plane).setShininess(20);
    (*plane).setSpecular(0.6, 0.4, 0.2);
    (*plane).setRefraction(0);

    objects[2] = plane;

    /* Right wall. */
    vector normalOne = {-1, 0, 0};
    plane = new Plane(800,0,0, normalOne, 0.0,0.0,0.0);
    (*plane).setReflection(0.9);
    (*plane).setShininess(50);
    (*plane).setSpecular(1, 1, 1);
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
    Sphere *sphere = new Sphere(800.0,600, 5600.0, 380.0, 1.0, 0.0, 0.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setRefraction(0.0);

    objects[0] = sphere;

    sphere = new Sphere(380.0,220.0, 500.0, 250.0, 0.0, 0.0, 1.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setRefraction(0.0);

    objects[1] = sphere;

    /* Planes initialization. */

    /* Ground. */
    vector normalZero = {0, 1, 0};
    Plane *plane = new Plane(0,0,0, normalZero, 0.0,0.0,0.7);
    (*plane).setReflection(0.0);
    (*plane).setShininess(20);
    (*plane).setSpecular(0.6, 0.4, 0.2);
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
    (*sphere).setRefraction(0.0);

    objects[0] = sphere;

    sphere = new Sphere(380.0,220.0, 4100.0, 50.0, 0.0, 0.0, 1.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
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
    (*plane).setRefraction(0);

    objects[2] = plane;

    /* Right wall. */
    vector normalOne = {-1, 0, 0};
    plane = new Plane(800,0,0, normalOne, 0.0,0.0,0.0);
    (*plane).setReflection(0.9);
    (*plane).setShininess(50);
    (*plane).setSpecular(1, 1, 1);
    (*plane).setRefraction(0);

    objects[3] = plane;

    /* Back wall.*/
    vector normalTwo = {0, 0, -1};
    plane = new Plane(0,0,20000, normalTwo, 0.6,0.8,0.2);
    (*plane).setReflection(0.2);
    (*plane).setShininess(50);
    (*plane).setSpecular(0.2, 0.2, 0.2);
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
    (*sphere).setRefraction(0.3);

    objects[0] = sphere;

    sphere = new Sphere(380.0,280.0, 300.0, 50.0, 0.0, 0.0, 1.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(50);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setRefraction(0.0);

    objects[1] = sphere;

    /* Planes initialization. */

    /* Ground. */
    vector normalZero = {0, 1, 0};
    Plane *plane = new Plane(0,0,0, normalZero, 0.0,0.0,0.3);
    (*plane).setReflection(0.5);
    (*plane).setShininess(20);
    (*plane).setSpecular(0.6, 0.6, 0.6);
    (*plane).setRefraction(0.0);

    objects[2] = plane;

    /* Back wall.*/
    vector normalTwo = {0, 0, -1};
    plane = new Plane(0,0,100000, normalTwo, 0.1,0.1,0.8);
    (*plane).setReflection(0.5);
    (*plane).setShininess(0.1);
    (*plane).setSpecular(0.1, 0.1, 0.1);
    (*plane).setRefraction(0);

    objects[3] = plane;

    /* Lights initialization. */
    lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[1] = Light(300,10000,-6000, 1.0, 1, 1, 1);
}

/* SCENE DESCRIPTION:
 *    -> Cube test.
 */
void sceneFive()
{
    /* First, allocates enough space for all the structures.*/
    noObjects = 2;
    noLights = 2;

    objects = new Object *[noObjects];
    lights = new Light[noLights];

    /* Spheres initialization. */
    Cube *cube = new Cube(200.0,300, 500.0, 200,200,200, 1.0, 0.0, 0.0);
    (*cube).setReflection(0.0);
    (*cube).setShininess(50);
    (*cube).setSpecular(1, 1, 1);
    (*cube).setRefraction(0.0);

    objects[0] = cube;

    /* Back wall.*/
    vector normalOne = {1, 0, 0};
    Plane *plane = new Plane(0,0,0, normalOne, 0.1,0.1,0.8);
    (*plane).setReflection(0.0);
    (*plane).setShininess(50);
    (*plane).setSpecular(0.1, 0.1, 0.1);
    (*plane).setRefraction(0);

    objects[1] = plane;

    /* Lights initialization. */
    //lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[0] = Light(300,400,-1000, 1.0, 1, 1, 1);
    lights[1] = Light(1000,400,500, 1.0, 1, 1, 1);
}

/* SCENE DESCRIPTION:
 *    -> Our mountain.
 */

void addTree(int objectNo, double x, double z)
{
     /* Cubes initialization. */
    Cube *cube = new Cube(x, 25, z, 20, 50, 10, 0.55, 0.27, 0.07);
    (*cube).setReflection(0.0);
    (*cube).setShininess(10);
    (*cube).setSpecular(1, 1, 1);
    (*cube).setRefraction(0.0);

    objects[objectNo] = cube;

        /* Spheres initialization. */
    Sphere *sphere = new Sphere(x, 65 , z, 30.0, 0.13, 0.55, 0.13);
    (*sphere).setReflection(0.2);
    (*sphere).setShininess(40);
    (*sphere).setSpecular(0.2, 0.8, 0.2);
    (*sphere).setRefraction(0.0);

    objects[objectNo + 1] = sphere;

    return;
}

void addMountainBlock(int objectNo, int i, double x, double y, double z, double xS, double yS, double zS,
        double e1, double e11, double e2, double e22, double e3, double e33)
{
        /* Height definition */
        Cube *cube = new Cube(x, y, z, xS, yS, zS,
        /* Colour definition */
        0.36 + (pow(NEPER, e1*i))*e11,
            0.25 + (pow(NEPER, e2*i))*e22,
                0.2 + (pow(NEPER, e3*i))*e33);

        (*cube).setReflection(0.0);
        (*cube).setShininess(50);
        (*cube).setSpecular(1, 1, 1);
        (*cube).setRefraction(0.0);

        objects[objectNo] = cube;
}

void addMountainBlockTwo(int objectNo, int i, double x, double y, double z, double xS, double yS, double zS,
        double e1, double e11, double e2, double e22, double e3, double e33)
{
        /* Height definition */
        Cube *cube = new Cube(x, y, z, xS, yS, zS,
        /* Colour definition */
        0.36 + (pow(NEPER, e1*i))*e11,
            0.25 + (pow(NEPER, e2*i))*e22,
                0.2 + (pow(NEPER, e3*i))*e33);

        (*cube).setReflection(0.0);
        (*cube).setShininess(100);
        (*cube).setSpecular(0.2, 0.2, 0.2);
        (*cube).setRefraction(0.0);

        objects[objectNo] = cube;
}

void sceneMountain()
{
    /* First, allocates enough space for all the structures.*/
    int i;

    noObjects = 114;
    noLights = 2;

    objects = new Object *[noObjects];
    lights = new Light[noLights];

    /* Back wall: the sky..*/
    vector normalOne = {0, 0, -1};
    Plane *plane = new Plane(0,0,10000, normalOne, 0.55,0.27,0.075);
    (*plane).setReflection(0.0);
    (*plane).setShininess(50);
    (*plane).setSpecular(0.1, 0.1, 0.1);
    (*plane).setRefraction(0);

    objects[0] = plane;

    /* Ground. */
    vector normalZero = {0, 1, 0};
    plane = new Plane(0,0,0, normalZero, 0.35,0.27,0.075);
    (*plane).setReflection(0.0);
    (*plane).setShininess(20);
    (*plane).setSpecular(0.6, 0.6, 0.6);
    (*plane).setRefraction(0.0);

    objects[1] = plane;

    /* Cubes initialization. */
    Cube *cube;

    for (i = 2; i <= 35; i++)
    {           
        if (i <= 35/6)
            addMountainBlock(i, i, 0.0, 50*(i-1), 1500.0, 3000 - (3000.0/35)*i*4,100, 1000 - (1000.0/35)*i*4,
                    0.1423, 0.00894, 0.1471, 0.00894, 0.1499, 0.00890);
        else
            addMountainBlock(i, i, 0.0, 50*(i-1), 1500.0, 5000/i,100, 2000/i,
                    0.1423, 0.00894, 0.1471, 0.00894, 0.1499, 0.00890);
    }

    for (i = 2; i <= 21; i++)
        addMountainBlock(i+34, i, 1500.0, 50*(i-1), 1000.0, 2000/i, 100, 700/i,
                    0.2323, 0.00984, 0.2371, 0.00984, 0.2399, 0.00980);

    for (i = 2; i <= 21; i++)
        addMountainBlock(i+54, i, 100.0, 50*(i-1), 500.0, 2000/i, 100, 700/i,
                    0.2323, 0.00984, 0.2371, 0.00984, 0.2399, 0.00980);

    for (i = 2; i <= 14; i++)
        addMountainBlock(i+74, i, 1200.0, 50*(i-1), 600.0, 1200/i, 100, 300/i,
                    0.2523, 0.00994, 0.2571, 0.00994, 0.2599, 0.00990);


    /* After adding all the mountains, we still add some blocks to join the
     * bottoms of each.
     */
    cube = new Cube(900.0, 30, 400.0, 800, 60, 250, 0.36, 0.25, 0.2);
    (*cube).setReflection(0.0);
    (*cube).setShininess(50);
    (*cube).setSpecular(1, 1, 1);
    (*cube).setRefraction(0.0);
    objects[89] = cube;


    cube = new Cube(-750.0, 30, 800.0, 250, 60, 800, 0.36, 0.25, 0.2);
    (*cube).setReflection(0.0);
    (*cube).setShininess(50);
    (*cube).setSpecular(1, 1, 1);
    (*cube).setRefraction(0.0);
    objects[90] = cube;

    /* And now the water in the middle of the mountains. */
    cube = new Cube(200.0, 20, 1000.0, 1800, 40, 850, 0.5, 0.3, 0.8);
    (*cube).setReflection(1.0);
    (*cube).setShininess(10);
    (*cube).setSpecular(0, 0, 0);
    (*cube).setRefraction(0.0);
    objects[91] = cube;

    /* Adding some trees to the scenario. */
    addTree(92, -50.0, 220.0);
    addTree(98, 200.0, 70.0);
    addTree(102, 290.0, 200.0);
    addTree(94, 500.0, 90.0);
    addTree(96, 700.0, 140.0);
    addTree(106, 950.0, 200.0);
    addTree(108, 1150.0, 50.0);
    addTree(100, 1500.0, 135.0);
    addTree(104, 1750.0, 270.0);
    addTree(110, 1800.0, 500.0);
    addTree(112, 1450.0, 380.0);

    /* Lights initialization. */
    //lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[0] = Light(600,4000,-1000, 1.0, 1, 0.5, 0.5);
    lights[1] = Light(4000,800,500, 1.0, 1, 0.5, 0.5);
}

void sceneTemp()
{
    /* First, allocates enough space for all the structures.*/
    int i;

    noObjects = 136;
    noLights = 2;

    objects = new Object *[noObjects];
    lights = new Light[noLights];

    /* Back wall: the sky..*/
    vector normalOne = {0, 0, -1};
    Plane *plane = new Plane(0,0,10000, normalOne, 0.55,0.27,0.075);
    (*plane).setReflection(0.0);
    (*plane).setShininess(50);
    (*plane).setSpecular(0.1, 0.1, 0.1);
    (*plane).setRefraction(0);

    objects[0] = plane;

    /* Ground. */
    vector normalZero = {0, 1, 0};
    plane = new Plane(0,0,0, normalZero, 0.35,0.27,0.075);
    (*plane).setReflection(0.0);
    (*plane).setShininess(20);
    (*plane).setSpecular(0.6, 0.6, 0.6);
    (*plane).setRefraction(0.0);

    objects[1] = plane;

    /* The mountains at the horizon. */
    for (i = 2; i <= 35; i++)
    {
        if (i <= 35/6)
            addMountainBlockTwo(i, i, 0.0, 50*(i-1), 10000.0, 3000 - (3000.0/35)*i*4,100, 1000 - (1000.0/35)*i*4,
                    0.1423, 0.00894, 0.1471, 0.00894, 0.1499, 0.00890);
        else
            addMountainBlockTwo(i, i, 0.0, 50*(i-1), 10000.0, 5000/i,100, 2000/i,
                    0.1423, 0.00894, 0.1471, 0.00894, 0.1499, 0.00890);
    }

    for (i = 2; i <= 21; i++)
        addMountainBlockTwo(i+34, i, -1500.0, 50*(i-1), 10000.0, 2000/i, 100, 700/i,
                0.2323, 0.00984, 0.2371, 0.00984, 0.2399, 0.00980);

    for (i = 2; i <= 21; i++)
        addMountainBlockTwo(i+54, i, 1700.0, 50*(i-1), 10000.0, 2000/i, 100, 700/i,
                0.2323, 0.00984, 0.2371, 0.00984, 0.2399, 0.00980);

    for (i = 2; i <= 14; i++)
        addMountainBlock(i+74, i, 3300.0, 50*(i-1), 10000.0, 1200/i, 100, 300/i,
                0.2523, 0.00994, 0.2571, 0.00994, 0.2599, 0.00990);

    for (i = 2; i <= 14; i++)
        addMountainBlock(i+87, i, 5400.0, 50*(i-1), 10000.0, 1200/i, 100, 300/i,
                0.2523, 0.00994, 0.2571, 0.00994, 0.2599, 0.00990);

    for (i = 2; i <= 35; i++)
    {
        if (i <= 35/6)
            addMountainBlockTwo(i + 100, i, 7000.0, 50*(i-1), 10000.0, 3000 - (3000.0/35)*i*4,100, 1000 - (1000.0/35)*i*4,
                    0.1423, 0.00894, 0.1471, 0.00894, 0.1499, 0.00890);
        else
            addMountainBlockTwo(i + 100, i, 0.0, 50*(i-1), 10000.0, 5000/i,100, 2000/i,
                    0.1423, 0.00894, 0.1471, 0.00894, 0.1499, 0.00890);
    }

    /* Lights initialization. */
    //lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[0] = Light(600,4000,-1000, 1.0, 1, 0.5, 0.5);
    lights[1] = Light(4000,800,500, 1.0, 1, 0.5, 0.5);
}

/* SCENE DESCRIPTION:
 *    -> The chess scene.
 */
void sceneChess()
{
    /* Redefines the values for this specific scenario. */
    fadingCoeficient = 4000;
    fullLightLimit = 8000;

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
    (*sphere).setRefraction(0.0);

    objects[0] = sphere;

    sphere = new Sphere(400.0,300.0, 100.0, 50.0, 0.0, 0.0, 0.0);
    (*sphere).setReflection(0.0);
    (*sphere).setShininess(80);
    (*sphere).setSpecular(1, 1, 1);
    (*sphere).setRefraction(0.8);

    objects[1] = sphere;

    /* Planes initialization. */

    /* Ground. */
    vector normalZero = {0, 1, 0};
    PlaneChess *planeChess = new PlaneChess(0,0,0, normalZero, 250.0);
    (*planeChess).setReflection(0.0);
    (*planeChess).setShininess(0);
    (*planeChess).setSpecular(0, 0, 0);
    (*planeChess).setRefraction(0);

    objects[2] = planeChess;

    /* Right wall. */
    vector normalOne = {-1, 0, 0};
    Plane *plane = new Plane(2300,0,0, normalOne, 0.0,0.0,0.0);
    (*plane).setReflection(0.9);
    (*plane).setShininess(50);
    (*plane).setSpecular(1, 1, 1);
    (*plane).setRefraction(0);

    objects[3] = plane;

    /* Left wall. */
    vector normalTwo = {1, 0, 0};
    plane = new Plane(0,0,0, normalTwo, 0.0,0.0,0.0);
    (*plane).setReflection(0.9);
    (*plane).setShininess(50);
    (*plane).setSpecular(1, 1, 1);
    (*plane).setRefraction(0);

    objects[4] = plane;

    noObjects = 3;

    /* Lights initialization. */
    lights[0] = Light(300,10000,6000, 1.0, 1, 1, 1);
    lights[1] = Light(300,400,-6000, 1.0, 1, 1, 1);
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
        case 5: sceneFive(); return;
        case 6: sceneMountain(); return;
        case 7: sceneChess(); return;
        case 8: sceneTemp(); return;
        default: sceneOne(); printf("WARNING: No valid scenarion has been choosen. Will set scenario one...\n");
    }

    return;
}