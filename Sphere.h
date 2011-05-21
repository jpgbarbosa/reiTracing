#ifndef _H_Sphere#define _H_Sphere/* Needed libraries. */#include <cmath>/* Defines the needed classes and their headers. */class Ray;#include "BasicStructures.h"#include "Object.h"/* Header for the Sphere class. */class Sphere : public Object{private:	/* - - - - - - - - - - - - ATTRIBUTES - - - - - - - - - -*/	/* The the radius of the sphere. */	double radius;public:	/* - - - - - - - CONSTRUCTOR & DESTRUCTOR - - - - - - - -*/	/* Constructor & destructor. */	explicit Sphere(double x, double y, double z, double rad, double rC, double gC, double bC);	explicit Sphere();	~Sphere();	/* - - - - - - - OTHER METHODS - - - - - - - -*/	/* Determinates whether the ray intersects this sphere or not. */	bool intersects(Ray &ray, double &rT0, double &rT1);        void newDirection(Ray &ray, double &t);        void refractionRedirection(Ray &ray, double t);        void intersectionPointNormal(Ray &ray, vector &normalInt);		/* - - - - - - - GETTERS & SETTERS - - - - - - - -*/	double getRadius();	};#endif