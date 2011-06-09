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

using namespace std;

/* The screen definition. */
int screenWidth = SCREEN_W;
int screenHeight = SCREEN_H;
int screenSize = SCREEN_W*SCREEN_H;

/* This array will hold all the colours for all the pixels in the screen. */
colour image[SCREEN_W][SCREEN_H];

/* Definition of all objects in the scene, as well as the camera. */
point camera;

int noObjects;
Object **objects;

int noLights;
Light *lights;


void display()
{
    int i, j;

    /* Passes into an array all the colours gathered in the matrix
     * image, so we can use it in the DrawPixels.
     */
    float *pixels = new float[screenSize*3];

    for( i = 0; i < screenHeight; i++)
            for (j = 0; j < screenWidth; j++)
            {
                    pixels[i*(screenWidth*3) + j*3] = image[j][i].r;
                    pixels[i*(screenWidth*3) + j*3 + 1] = image[j][i].g;
                    pixels[i*(screenWidth*3) + j*3 + 2] = image[j][i].b;
            }

    antiAliasing(pixels, ANTIALIASING_TIMES);

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
    camera.x = 400;
    camera.y = 300;
    camera.z = -1000;

    /* Builds the right scene. */
    buildScene(2);

    /* Starts the ray tracing process. */
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