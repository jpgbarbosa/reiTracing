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

/* The visualization type. */
int visualizationType;


void display()
{
    int i, j;

    /* Passes into an array all the colours gathered in the matrix
     * image, so we can use it in the DrawPixels.
     */
    float *pixels = new float[(screenSize/4)*3];

    /* An antialiasing technique. Basically, we create a image four times than
     * the final one and when generating it, we compress this bigger image into
     * a smaller one, smoothing the differences between colours. This way, it's
     * like each ray contributes to 25% of the final image.
     */
    for( i = 0; i < screenHeight/2 - 1; i++)
    {
        for (j = 0; j < screenWidth/2 - 1; j++)
        {
            /* RED. */
            double value;

           value = image[2*j][2*i].r + image[2*j][2*(i+1)].r +
                   image[2*(j+1)][2*i].r + image[2*(j+1)][2*(i+1)].r;
           pixels[i*(screenWidth/2*3) + j*3] = value / 4;

            /* GREEN. */
            value = image[2*j][2*i].g + image[2*j][2*(i+1)].g +
                    image[2*(j+1)][2*i].g + image[2*(j+1)][2*(i+1)].g;
            pixels[i*(screenWidth/2*3) + j*3 + 1] = value / 4;

            /* BLUE. */
            value = image[2*j][2*i].b + image[2*j][2*(i+1)].b +
                    image[2*(j+1)][2*i].b + image[2*(j+1)][2*(i+1)].b;
            pixels[i*(screenWidth/2*3) + j*3 + 2] = value / 4;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Writes a block of pixels to the framebuffer. */
    glDrawPixels(screenWidth/2,screenHeight/2,GL_RGB,GL_FLOAT, pixels);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(screenWidth/2, screenHeight/2);
    glutCreateWindow("Our Fantastic Ray Tracer");

    visualizationType = LOOKING_AHEAD;

    /* Camera initialization. */
    switch (visualizationType)
    {
        case LOOKING_AHEAD:
                camera.x = 800;
                camera.y = 600;
                camera.z = -1000;
                break;
        case LOOKING_DOWN:
                camera.x = 800;
                camera.y = 1500;
                camera.z = 600;
                break;
    }

    /* Builds the right scene. */
    buildScene(6);

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