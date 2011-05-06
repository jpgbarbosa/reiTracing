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
#define MAX_DEPTH 1
#define NO_SPHERES 2
#define NO_LIGHTS 1

using namespace std;
/* The screen definition. */
int screenWidth = SCREEN_W;
int screenHeight = SCREEN_H;
int screenSize = SCREEN_W*SCREEN_H;

/* This array will hold all the colours for all the pixels in the screen. */
colour image[SCREEN_W][SCREEN_H];

/* Definition of all objects in the scene, as well as the camera. */
point camera; // TODO: For now, we are assuming that the view plan is at z = 0;

int noSpheres = NO_SPHERES;
Sphere spheres[NO_SPHERES];

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
	double minT = -1, t;

	/* Goes throught all the objects. TODO: Improve this to more objects. */
	for (i = 0; i < noSpheres; i++)
		if (spheres[i].intersects(ray, t))
		{
			/* Finds the closest. */
			if (t < minT || minT == -1)
			{
				minT = t;
				index = i;
			}
		}
	
	/* We have found at least one intersection. */
	if (minT != -1)
	{
		/* Used in the Blinn-Phong calculation. */
		vector oldDir;
		oldDir.x = ray.getDir().x;
		oldDir.y = ray.getDir().y;
		oldDir.z = ray.getDir().z;
		
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
			
			bool inShadow = false;
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
			for (i = 0; i < noSpheres && !inShadow; i++)
				//TODO: Does the second part of the && is correct?
				if (spheres[i].intersects(toLightRay, t) && i != index)
					inShadow = true;
			
			/* We aren't in shadow of any other object. Therefore, we have to calculate
			 * the contribution of this light to the final result.
			 */
			if (!inShadow)
			{
				/* The Lambert Effect. Depending on the direction of the light, it might
				 * be more or less intense.
				 */
				double lambert = (toLightRay.getDir() * normal * ray.getIntensity());
				
				/* Updates the colour of the ray. */
				ray.increaseR(lambert*lights[z].getR()*spheres[index].getR());
				ray.increaseG(lambert*lights[z].getG()*spheres[index].getG());
				ray.increaseB(lambert*lights[z].getB()*spheres[index].getB());
			
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
                    blinnCoef = ray.getIntensity() * powf(blinnCoef, spheres[index].getShininess());
					ray.increaseR(blinnCoef * spheres[index].getSpecular().r  * lights[z].getIntensity());
					ray.increaseG(blinnCoef * spheres[index].getSpecular().g  * lights[z].getIntensity());
					ray.increaseB(blinnCoef * spheres[index].getSpecular().b  * lights[z].getIntensity());
				}
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
		ray.normalizeColour();
		image[ray.getHPos()][ray.getWPos()].r = ray.getR();
		image[ray.getHPos()][ray.getWPos()].g = ray.getG();
		image[ray.getHPos()][ray.getWPos()].b = ray.getB();
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
			/*TODO: Change the starting point and the direction later. */
			Ray ray(x,y,-1000.0, y, x);
			ray.setDirection(0,0,1.0);
			//point pixelPoint = {(0.5 + x, 0.5 + y, 0.0)};
			//vector dir = pixelPoint - camera;
			//ray.setDirection(dir);
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
			pixels[i*(screenWidth*3) + j*3] = image[j][i].r;
			pixels[i*(screenWidth*3) + j*3 + 1] = image[j][i].g;
			pixels[i*(screenWidth*3) + j*3 + 2] = image[j][i].b;
		}
	/* Aliasing techniques:
	 * Given all the calculated colours from the ray tracing process, we
	 * pick up all the values around it and calculate its mean. That mean
	 * will be the final colour of the pixel.
	 */	
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
			
			pixels[i*(screenWidth*3) + j*3 + 2] = value / 9;
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
	glutCreateWindow("Our Ray Tracer");
	
	/* Camera initialization. */
	camera.x = 300;
	camera.y = 400;
	camera.z = -1000;
	
	/* Spheres initialization. */
	spheres[0] = Sphere(500.0,300, 100.0, 80.0, 1.0, 0.0, 0.0);
	spheres[0].setReflection(0.01);
	spheres[0].setShininess(50);
	spheres[0].setSpecularR(1);
	spheres[0].setSpecularG(1);
	spheres[0].setSpecularB(1);
	spheres[0].setDiffuseR(0.9);
	spheres[0].setDiffuseG(0.0);
	spheres[0].setDiffuseB(0.0);
	spheres[1] = Sphere(380.0,220.0,-100.0, 50.0, 0.0, 0.0, 1.0);
	spheres[1].setReflection(0.01);
	spheres[1].setShininess(50);
	spheres[1].setSpecularR(1);
	spheres[1].setSpecularG(1);
	spheres[1].setSpecularB(1.0);
	spheres[1].setDiffuseR(0.0);
	spheres[1].setDiffuseG(0.0);
	spheres[1].setDiffuseB(0.9);
	
	/* Lights initialization. */
	lights[0] = Light(0,0,-1000, 1.0, 1, 1, 1);
	
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