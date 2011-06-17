#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
/* For threads. */
#include <pthread.h>

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

/* Threads variables. */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t goOn = PTHREAD_COND_INITIALIZER;
pthread_t *thr_array;

int noObjects;
Object **objects;

int noLights;
Light *lights;

/* The visualization type. */
int visualizationType;

/* Defines the fading coeficient of a light according with the distance. */
long long fadingCoeficient = 5000;
long long fullLightLimit = 15000;

/* Passes into an array all the colours gathered in the matrix
 * image, so we can use it in the DrawPixels.
 */
float *pixels = new float[(screenSize/4)*3];

void display()
{
    int i, j;

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

    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    //glutMouseFunc(mouse_button);
    //glutMotionFunc(mouse_motion);
    //glutKeyboardFunc(keyboard);
    //glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glPointSize(2);

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
    if (argc > 1)
        buildScene(atoi(argv[1]));
    else
        buildScene(6);

    /* Starts the ray tracing process by creating two threads. */
    thr_array = (pthread_t *)malloc(2*sizeof(pthread_t));
    int threadOne = 0;
    pthread_create(&thr_array[0], NULL, renderImage, &threadOne);
    int threadTwo = 1;
    pthread_create(&thr_array[1], NULL, renderImage, &threadTwo);

    glutMainLoop();

    /* Now waits for the thread to conclude their work. */
    /*printf("Waiting for threads...\n");
    pthread_join(thr_array[0],NULL);
    pthread_join(thr_array[1],NULL);
    printf("Finished rendering!\n"); */

    return 0;
}