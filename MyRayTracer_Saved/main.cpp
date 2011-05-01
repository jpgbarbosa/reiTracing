#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

/* Defines the needed classes and their headers. */
#include "Sphere.h"
#include "Ray.h"
#include "Light.h"
#include "BasicStructures.h"

#define SCREEN_W 800
#define SCREEN_H 600
#define MAX_DEPTH 5
#define NO_SPHERES 1
#define NO_LIGHTS 1

/* The screen definition. */
int screenWidth = SCREEN_W;
int screenHeight = SCREEN_H;
int screenSize = SCREEN_W*SCREEN_H;

/* This array will hold all the colours for all the pixels in the screen. */
pixelColour image[SCREEN_W][SCREEN_H];

/* Definition of all objects in the scene. */
int noSpheres = NO_SPHERES;
Sphere spheres[NO_SPHERES] = {Sphere(300,400,0, 200, 1, 0, 0)};

int noLights = NO_LIGHTS;
Light lights[NO_LIGHTS] = {Light(0,0,0, 1.0, 1, 1, 1)};

/* Return values:
 * -1: Hasn't hit any object.
 *  0: Has hit a regular object.
 *  1: Has hit a light.
 */
 //TODO: Maybe return 0 and 1 are the same!
int rayTracer(Ray ray, int depth)
{
	int i, z, index, outcome;
	double minT = -1, t;
	bool hitLight = false;
	
	/* We have reached the limit of recursivity for ray tracing.
	 * Consequently, we assume that we can't reach the light and
	 * therefore, the pixel colour will be black, corresponding
	 * to the absence of colour.
	 */
	
	//TODO: We may calculate the distance to the light and make
	// some kind of fading, instead of just paiting it black.
	// Also, the background now will be white, while it should be black.
	if (depth == MAX_DEPTH)
	{
		image[ray.getHPos()][ray.getWPos()].r = ray.getR();
		image[ray.getHPos()][ray.getWPos()].g = ray.getG();
		image[ray.getHPos()][ray.getWPos()].b = ray.getB();
		
		//TODO: Correct value to return?
		return -1;
	}
	/* If this ray has hit the light, we don't need to perform 
	 * calculations any further.
	 * TODO: Maybe improve this and change the location of this.
	 */
	else if (hitLight)
	{
		image[ray.getHPos()][ray.getWPos()].r = ray.getR();
		image[ray.getHPos()][ray.getWPos()].g = ray.getG();
		image[ray.getHPos()][ray.getWPos()].b = ray.getB();
		
		return 1;
	}
	
	/* Goes throught all the objects. TODO: Improve this to more objects. */
	for (i = 0; i < noSpheres; i++)
		if (spheres[i].intersects(ray, t))
			/* Finds the closest. */
			if (t < minT || minT == -1)
			{
				minT = t;
				index = i;
			}
	
	/* We have found at least one intersection. */
	if (minT != -1)
	{
		/* Calculate the new direction of the ray. */
		ray.newDirection(minT, spheres[index]);
			
		/* Then, calculate the lighting at this point. */
		for (z = 0; z < noLights; z++)
		{
			/* The directional vector between the intersection point and the light. */
			double toLight[3];
			
			toLight[0] = lights[z].getX() - ray.getInitX();
			toLight[1] = lights[z].getY() - ray.getInitY();
			toLight[2] = lights[z].getZ() - ray.getInitZ();
			
			bool isInShadow = false;
			/* Now, we have to see if we are in the shadow of any other object. */
			for (i = 0; i < noSpheres && !isInShadow; i++)
				if (spheres[i].intersects(ray, t))
					isInShadow = true;
			
			/* Updates the colour of the ray. */
			ray.updateR(spheres[index].getR());
			ray.updateG(spheres[index].getG());
			ray.updateB(spheres[index].getB());
			
			
		}
	}
	/* If we don't have any intersection. */
	else
		return -1;
			
	
	/* We need to move to the next level of recursivity. */
	outcome = rayTracer(ray, depth + 1);
	
	//TODO: Handle the outcome.
	
	return outcome;
}

void renderImage()
{
	int i, j;
	
	
	for (i = 0; i < screenHeight; i++)
		for (j = 0; j < screenWidth; j++)
		{
			/*TODO: Change the starting point and the direction later. */
			Ray ray(j,i,-1000.0, i, j);
			ray.setDirection(0,0,1.0);
			ray.normalize();
			ray.setColour(1, 1, 1);
			rayTracer(ray, 0);
			
		}
   /*for each pixel i, j in the image
      ray.setStart(0, 0, 0);   // ro
      ray.setDir  ((.5 + i) * tan(fovx)* 2 / m,
		   	    (.5 + j) * tan(fovy)* 2 / n,
			    1.0);		 // rd
      ray.normalize();
      image[i][j] = rayTrace(ray); */
}


void display()
{
	int i, j;
	
	/* Passes into an array all the colours gathered in the matrix 
	 * image, so we can use it in the DrawPixels.
	 */
	float* pixels = new float[screenSize*3];

	for( i = 0; i < screenHeight; i++)
		for (j = 0; j < screenWidth; j++)
		{
			pixels[i*(screenWidth*3) + j*3] = image[i][j].r;
			pixels[i*(screenWidth*3) + j*3 + 1] = image[i][j].g;
			pixels[i*(screenWidth*3) + j*3 + 2] = image[i][j].b;
		}
		
	
	/*for( i = 0; i < screenHeight; i++)
		for (j = 0; j < screenWidth; j++)
		{
			float no;
			if (j > 600)
				no = 1;
			else
				no = 0.0;
			
			pixels[i*(screenWidth*3) + j*3] = no;
			pixels[i*(screenWidth*3) + j*3 + 1] = no;
			pixels[i*(screenWidth*3) + j*3 + 2] = no;
		}
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Writes a block of pixels to the framebuffer. */

	glDrawPixels(screenWidth,screenHeight,GL_RGB,GL_FLOAT, pixels);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Our Ray Tracer");
	
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