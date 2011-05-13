#ifndef _H_Ray#define _H_Ray/* Needed libraries. */#include <string>/* Defines the needed classes and their headers. */class Sphere;class Plane;#include "BasicStructures.h"/* Header for the Ray class. */class Ray{private:	/* - - - - - - - - - - - - ATTRIBUTES - - - - - - - - - -*/	/* The starting point of the ray and its direction. */	point origin;		vector direction;	/* The corresponding pixel in the final image for this ray. */	int wPos, hPos;	/* The colour for this ray. */	colour c;	double intensity;        /* If this is a ray cast from the camera or a ray that connects an         * intersection point to a light.         */        bool isToLight;        double distanceToLight;        public:	/* - - - - - - - CONSTRUCTOR & DESTRUCTOR - - - - - - - -*/	/* Constructor & destructor. */	explicit Ray(double x, double y, double z, int w, int h);	~Ray();	/* - - - - - - - OTHER METHODS - - - - - - - -*/	void normalize();	/* Sets the new direction of the ray after an intersection. */	void newDirection(double t, Sphere &sphere);        void newDirection(double t, Plane &plane);	double normalizeColour();		/* - - - - - - - GETTERS & SETTERS - - - - - - - -*/	int getWPos();	int getHPos();	vector getDir();	point getOrigin();	void setDirection(double x, double y, double z);	void setDirection(vector &v);	void setOrigin(point &p);        void setIsToLight(bool v, double d);        bool isToLightRay();        double getToLightDistance();		double getR();	double getG();	double getB();	void increaseR(double per);	void increaseG(double per);	void increaseB(double per);		double getIntensity();	void multIntensity(double v);};#endif