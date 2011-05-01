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
Sphere spheres[NO_SPHERES] = {Sphere(300,400,0, 100, 1.0, 1, 0.1, 0.1)};

int noLights = NO_LIGHTS;
Light lights[NO_LIGHTS] = {Light(500,300,200, 1.0, 1, 1, 1)};


void rayTracer(Ray ray, int depth)
{
	int i, z, index;
	double minT = -1, t;
	
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
		ray.setIntersected(true);
		/* Calculate the new direction of the ray. */
		ray.newDirection(minT, spheres[index]);
			
		/* Then, calculate the lighting at this point. */
		for (z = 0; z < noLights; z++)
		{
			/* The directional vector between the intersection point and the light. */
			vector toLight;
			toLight = lights[z].getCentre() - ray.getOrigin();

			/* We also need to calculate the normal at the intersection point. */
			vector normal = ray.getOrigin() - spheres[index].getCentre();
			double length = sqrtf(normal*normal);
			normal /= length;
			
			bool inShadow = true;
			/* If the normal is perpendicular or is in opposite direction of the light,
			 * we can skip this light because it's not going to light the intersection
			 * point.
			 */
			if (normal * toLight <= 0.0)
				continue;

			/* Now, we have to see if we are in the shadow of any other object.
			 * For that, we create a temporary ray that goes from the intersection
			 * point to the light spot.
			 */
			Ray toLightRay = Ray(ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z, 0, 0);
			toLightRay.setDirection(toLight);
			toLightRay.normalize();
			for (i = 0; i < noSpheres && inShadow; i++)
				if (spheres[i].intersects(toLightRay, t))
					inShadow = false;
			
			/* We aren't in shadow of any other object. Therefore, we have to calculate
			 * the contribution of this light to the final result.
			 */
			if (!inShadow)
			{
				/* The Lambert Effect. Depending on the direction of the light, it might
				 * be more or less intense.
				 */
				double lambert = (toLightRay.getDir() * normal * lights[z].getIntensity());
				
				/* Updates the colour of the ray. */
				ray.increaseR(lambert*lights[z].getR()*spheres[index].getR());
				ray.increaseG(lambert*lights[z].getG()*spheres[index].getG());
				ray.increaseB(lambert*lights[z].getB()*spheres[index].getB());
			}	
		}
		
		ray.multIntensity(spheres[index].getReflection());
	}	
	
	/* We have reached the limit of recursivity for ray tracing.
	 * Consequently, we assume that we can't reach the light and
	 * therefore, the pixel colour will be black, corresponding
	 * to the absence of colour.
	 * If we don't have any intersection, there's no point keep
	 * calculating the ray tracing. Also, the ray might not carry
	 * any more energy.
	 */
	if (minT == -1 || depth == MAX_DEPTH || ray.getIntensity() == 0.0)
	{
		if (ray.hasIntersected())
		{
			ray.normalizeColour();
			image[ray.getHPos()][ray.getWPos()].r = ray.getR();
			image[ray.getHPos()][ray.getWPos()].g = ray.getG();
			image[ray.getHPos()][ray.getWPos()].b = ray.getB();
		}
		/* Background colour. */
		else
		{
			image[ray.getHPos()][ray.getWPos()].r = 0;
			image[ray.getHPos()][ray.getWPos()].g = 0;
			image[ray.getHPos()][ray.getWPos()].b = 0;
		}
	
	}
	/* We need to move to the next level of recursivity. */	
	else
		rayTracer(ray, depth + 1);
	
	return;
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